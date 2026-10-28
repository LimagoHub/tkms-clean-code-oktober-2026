//
// Created by JoachimWagner on 01.12.2025.
//

#pragma once
#include <memory>
#include "Calculator.h"
#include "CalculatorImpl.h"
#include "CalculatorLogger.h"
#include "CalculatorSecure.h"

namespace math {
    using CalculatorPointer = std::unique_ptr<Calculator>;

    class CalculatorBuilder {

        bool logger{false};
        bool secure{false};

    public:
        CalculatorBuilder& withLogger() {
            logger = true;
            return *this;
        }

        CalculatorBuilder& withSecure() {
            secure = true;
            return *this;
        }

        CalculatorPointer build() {
            CalculatorPointer calc = std::make_unique<CalculatorImpl>();
            if (logger) calc = std::make_unique<CalculatorLogger>(std::move(calc));
            if (secure) calc = std::make_unique<CalculatorSecure>(std::move(calc));
            return calc;
        }
    };

} // math
