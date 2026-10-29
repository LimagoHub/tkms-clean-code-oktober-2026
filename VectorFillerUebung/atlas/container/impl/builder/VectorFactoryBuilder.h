//
// Created by JoachimWagner on 28.10.2026.
//

#pragma once

#include "../../IVectorFactory.h"
#include "../../../time/IStopwatch.h"

#include "../../../generator/IGeneratorFactory.h"

#include "../sequential/VectorFactorySequentialImpl.h"
#include "../parallel/VectorFactoryParallelImpl.h"
#include "../parallel/VectorFactoryAutoImpl.h"
#include "../decorator/VectorFactoryLoggerDecorator.h"
#include "../decorator/VectorFactorySecureDecorator.h"
#include "../decorator/VectorFactoryBenchmarkDecorator.h"

namespace atlas::container {

    template<class T>
    class VectorFactoryBuilder {
        using FactoryPtr          = std::unique_ptr<IVectorFactory<T>>;
        using GeneratorFactoryPtr = std::unique_ptr<generator::IGeneratorFactory<T>>;
        using StopwatchPtr        = std::unique_ptr<time::IStopwatch>;

        public:
        VectorFactoryBuilder() = default;

        /*
        auto withStrategy(Strategy strategy) -> VectorFactoryBuilder& {
            strategy_ = strategy;
            return *this;
        }
        */

        auto withThreadcount(size_t threadcount) -> VectorFactoryBuilder& {
            threadcount_ = threadcount;
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
            return applyOptionalDecorators(createCoreFactory(std::move(generatorFactory)));
        }

    private:

        auto createCoreFactory(GeneratorFactoryPtr generatorFactory) -> FactoryPtr {

            switch (threadcount_) {
                case 0:
                    return std::make_unique<VectorFactoryAutoImpl<T>>(std::move(generatorFactory));

                case 1:
                    return std::make_unique<VectorFactorySequentialImpl<T>>(std::move(generatorFactory->create()));

                default:
                    return std::make_unique<VectorFactoryParallelImpl<T>>(std::move(generatorFactory), threadcount_);

            }



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

        size_t       threadcount_{1};
        bool         isLoggingEnabled_{false};
        bool         isSecurityEnabled_{false};
        StopwatchPtr stopwatch_{nullptr};
    };
}
