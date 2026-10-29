#pragma once

#include <memory>
#include <utility>
#include <stdexcept>

#include "../../IVectorFactory.h"
#include "../../../generator/IGeneratorFactory.h"
#include "../../../time/IStopwatch.h"

#include "../sequential/VectorFactorySequentialImpl.h"
#include "../parallel/VectorFactoryAutoImpl.h"
#include "../parallel/VectorFactoryParallelImpl.h"
#include "../parallel/VectorFactoryThreadpoolImpl.h"
#include "../parallel/VectorFactoryThreadpoolLoopImpl.h"
#include "../decorator/VectorFactoryBenchmarkDecorator.h"
#include "../decorator/VectorFactoryLoggerDecorator.h"
#include "../decorator/VectorFactorySecureDecorator.h"

namespace atlas::container {

    enum class Strategy { Sequential, Auto, Parallel, Threadpool, ThreadpoolLoop };

    template<class T>
    class VectorFactoryBuilder {
        using FactoryPtr          = std::unique_ptr<IVectorFactory<T>>;
        using GeneratorFactoryPtr = std::unique_ptr<generator::IGeneratorFactory<T>>;
        using StopwatchPtr        = std::unique_ptr<time::IStopwatch>;

    public:
        VectorFactoryBuilder() = default;

        auto withStrategy(Strategy strategy) -> VectorFactoryBuilder& {
            strategy_ = strategy;
            return *this;
        }

        auto withThreadCount(size_t count) -> VectorFactoryBuilder& {
            threadCount_ = count;
            return *this;
        }

        auto enableLogging() -> VectorFactoryBuilder& {
            isLoggingEnabled_ = true;
            return *this;
        }

        auto enableSecurity() -> VectorFactoryBuilder& {
            isSecurityEnabled_ = true;
            return *this;
        }

        auto withBenchmark(StopwatchPtr stopwatch) -> VectorFactoryBuilder& {
            stopwatch_ = std::move(stopwatch);
            return *this;
        }

        auto build(GeneratorFactoryPtr generatorFactory) -> FactoryPtr {
            auto factory = createBaseStrategy(std::move(generatorFactory));
            return applyOptionalDecorators(std::move(factory));
        }

    private:
        auto createBaseStrategy(GeneratorFactoryPtr gb) const -> FactoryPtr {
            switch (strategy_) {
                case Strategy::Sequential:
                    return std::make_unique<VectorFactorySequentialImpl<T>>(gb->create());
                case Strategy::Auto:
                    return std::make_unique<VectorFactoryAutoImpl<T>>(std::move(gb));
                case Strategy::Parallel:
                    return std::make_unique<VectorFactoryParallelImpl<T>>(std::move(gb), threadCount_);
                case Strategy::Threadpool:
                    return std::make_unique<VectorFactoryThreadpoolImpl<T>>(std::move(gb), static_cast<uint32_t>(threadCount_));
                case Strategy::ThreadpoolLoop:
                    return std::make_unique<VectorFactoryThreadpoolLoopImpl<T>>(std::move(gb), static_cast<uint32_t>(threadCount_));
            }
            throw std::logic_error{"Unknown strategy"};
        }

        auto applyOptionalDecorators(FactoryPtr factory) -> FactoryPtr {
            if (isSecurityEnabled_)
                factory = std::make_unique<VectorFactorySecureDecorator<T>>(std::move(factory));
            if (isLoggingEnabled_)
                factory = std::make_unique<VectorFactoryLoggerDecorator<T>>(std::move(factory));
            if (stopwatch_)
                factory = std::make_unique<VectorFactoryBenchmarkDecorator<T>>(std::move(factory), std::move(stopwatch_));
            return factory;
        }

        Strategy     strategy_{Strategy::Sequential};
        size_t       threadCount_{1};
        bool         isLoggingEnabled_{false};
        bool         isSecurityEnabled_{false};
        StopwatchPtr stopwatch_{nullptr};
    };

}
