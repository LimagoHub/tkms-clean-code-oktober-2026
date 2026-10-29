#include <memory>
#include <thread>

#include "atlas/client/impl/ClientImpl.h"
#include "atlas/container/impl/builder/VectorFactoryBuilder.h"
#include "atlas/generator/impl/generic/GenericGeneratorImpl.h"
#include "atlas/generator/impl/random/MersenneTwisterNumberGenerator.h"
#include "atlas/time/impl/StopwatchImpl.h"

int main() {
    using namespace atlas;


    const size_t availableProcessors = std::thread::hardware_concurrency();
    std::cout << availableProcessors << std::endl;

    for (size_t threadCount = 1;threadCount <= availableProcessors+1; ++threadCount) {
        auto generator = std::make_unique<generator::MersenneTwisterNumberGenerator>();
        //auto generator = std::make_unique<generator::GenericGeneratorImpl>(0, [](int value) { return value + 5; });

        auto factory = container::VectorFactoryBuilder<int>{}
        .withBenchmark(std::make_unique<time::StopwatchImpl>())
        .enableLogging()
        .enableSecurity()
        .build(std::move(generator));

        client::VectorClientImpl client{std::move(factory)};

        client.processVector();
    }
    return 0;
}
