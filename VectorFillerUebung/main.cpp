#include <iostream>
#include <memory>
#include <thread>
#include <exception>

#include "atlas/container/impl/builder/VectorFactoryBuilder.h"
#include "atlas/generator/impl/random/MersenneTwisterNumberGeneratorFactory.h"
#include "atlas/time/impl/StopwatchImpl.h"
#include "atlas/client/impl/ClientImpl.h"

using namespace atlas;

auto runMeasurement(container::Strategy strategy, size_t threadCount) -> void {
    auto generatorBuilder = std::make_unique<generator::MersenneTwisterNumberGeneratorFactory>();

    container::VectorFactoryBuilder<int> builder;
    auto factory = builder
        .withStrategy(strategy)
        .withThreadCount(threadCount)
        .enableLogging()
        .enableSecurity()
        .withBenchmark(std::make_unique<time::StopwatchImpl>())
        .build(std::move(generatorBuilder));

    auto client = std::make_unique<client::VectorClientImpl>(std::move(factory));
    client->processVector();
}

auto main() -> int {
    try {
        const size_t maxThreads = std::thread::hardware_concurrency();

        std::cout << "==========================================" << std::endl;
        std::cout << "   TKMS PERFORMANCE BENCHMARK" << std::endl;
        std::cout << "==========================================" << std::endl;
        std::cout << "Verfuegbare logische Kerne: " << maxThreads << "\n" << std::endl;

        std::cout << "[Sequential]" << std::endl;
        runMeasurement(container::Strategy::Sequential, 1);
        std::cout << "------------------------------------------" << std::endl;

        std::cout << "[Auto]" << std::endl;
        runMeasurement(container::Strategy::Auto, maxThreads);
        std::cout << "------------------------------------------" << std::endl;

        for (size_t i = 2; i <= maxThreads; ++i) {
            std::cout << "[Parallel] " << i << " Threads" << std::endl;
            runMeasurement(container::Strategy::Parallel, i);
            std::cout << "------------------------------------------" << std::endl;
        }

        for (size_t i = 2; i <= maxThreads; ++i) {
            std::cout << "[Threadpool] " << i << " Threads" << std::endl;
            runMeasurement(container::Strategy::Threadpool, i);
            std::cout << "------------------------------------------" << std::endl;
        }

        for (size_t i = 2; i <= maxThreads; ++i) {
            std::cout << "[ThreadpoolLoop] " << i << " Threads" << std::endl;
            runMeasurement(container::Strategy::ThreadpoolLoop, i);
            std::cout << "------------------------------------------" << std::endl;
        }

        std::cout << "Saemtliche Messreihen erfolgreich abgeschlossen." << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "\n!!! KRITISCHER FEHLER !!!" << std::endl;
        std::cerr << "Grund: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
