//
// Created by JoachimWagner on 28.10.2026.
//

#pragma once

#include "../../IVectorFactory.h"
#include "../../../time/IStopwatch.h"

#include "../sequential/VectorFactorySequentialImpl.h"
#include "../decorator/VectorFactoryLoggerDecorator.h"
#include "../decorator/VectorFactorySecureDecorator.h"
#include "../decorator/VectorFactoryBenchmarkDecorator.h"

namespace atlas::container {

    template<class T>
    class VectorFactoryBuilder {
        using FactoryPtr          = std::unique_ptr<IVectorFactory<T>>;
        using GeneratorPtr = std::unique_ptr<generator::IGenerator<T>>;
        using StopwatchPtr        = std::unique_ptr<time::IStopwatch>;

        public:
        VectorFactoryBuilder() = default;



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

        auto build(GeneratorPtr generator) -> FactoryPtr {
            auto factory = std::make_unique<VectorFactorySequentialImpl<T>>(std::move(generator));
            return applyOptionalDecorators(std::move(factory));
        }

    private:


        auto applyOptionalDecorators(FactoryPtr factory) -> FactoryPtr {
            if (isSecurityEnabled_)
                factory = std::make_unique<VectorFactorySecureDecorator<T>>(std::move(factory));
            if (isLoggingEnabled_)
                factory = std::make_unique<VectorFactoryLoggerDecorator<T>>(std::move(factory));
            if (stopwatch_)
                factory = std::make_unique<VectorFactoryBenchmarkDecorator<T>>(std::move(factory), std::move(stopwatch_));
            return factory;
        }


        bool         isLoggingEnabled_{false};
        bool         isSecurityEnabled_{false};
        StopwatchPtr stopwatch_{nullptr};
    };
}
