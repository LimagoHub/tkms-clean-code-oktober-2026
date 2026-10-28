//
// Created by JoachimWagner on 30.06.2023.
//

#pragma once
#include <random>
#include <climits>
#include "../../IIntGenerator.h"
#include <memory>
#include <functional>

namespace atlas::generator {
    class GenericGeneratorImpl : public IIntGenerator{
    public:
        ~GenericGeneratorImpl() override = default;
        explicit GenericGeneratorImpl(int seed, const std::function<int(int)> &myFunc):
        value(seed), myFunc(myFunc){}

        [[nodiscard]] auto next() noexcept-> int override {
            int result = value;
            value = myFunc(value);
            return result;
        }

    private:
        int value{0};
        std::function<int(int)> myFunc;
    };

}