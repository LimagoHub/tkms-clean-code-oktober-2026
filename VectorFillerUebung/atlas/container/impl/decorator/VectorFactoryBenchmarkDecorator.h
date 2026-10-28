//
// Created by JoachimWagner on 12.03.2025.
//

#pragma once
#include <memory>
#include <iostream>
#include "../../IVectorFactory.h"
#include "../../../time/IStopwatch.h"

namespace atlas::container {

    template<class T>
    class VectorFactoryBenchmarkDecorator : public IVectorFactory<T> {
        using VectorPtr = std::unique_ptr<std::vector<T>>;
        using FactoryPtr = std::unique_ptr<IVectorFactory<T>>;
        using StopwatchPtr = std::unique_ptr<atlas::time::IStopwatch>;

    public:
        VectorFactoryBenchmarkDecorator(FactoryPtr vectorFactory, StopwatchPtr stopwatch)
            : vectorFactory_{std::move(vectorFactory)}, stopwatch_{std::move(stopwatch)} {}

        auto createAndFillVector(const size_t size) -> VectorPtr override {
            stopwatch_->start();
            auto result = vectorFactory_->createAndFillVector(size);
            stopwatch_->stop();
            std::cout << "Duration = " << stopwatch_->getDuration().count() << std::endl;
            return result;
        }

    private:
        FactoryPtr vectorFactory_;
        StopwatchPtr stopwatch_;
    };

}
