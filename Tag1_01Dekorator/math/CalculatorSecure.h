//
// Created by JoachimWagner on 01.12.2025.
//

#pragma once
#include <memory>
#include "CalculatorImpl.h"

namespace math {

    class CalculatorSecure: public Calculator{

        std::unique_ptr<Calculator> calculator;
    public:
        explicit CalculatorSecure(std::unique_ptr<Calculator> calculator) : calculator(std::move(calculator)) {}

        double add(double a, double b) override {
            std::cout << "Du kommst hier rein" << std::endl;
            return calculator->add(a,b);
        }

        double sub(double a, double b) override {
            return calculator->sub(a,b);
        }
    };

} // math
