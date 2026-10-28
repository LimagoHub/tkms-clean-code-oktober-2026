//
// Created by JoachimWagner on 01.12.2025.
//

#pragma once
#include<iostream>
#include "Calculator.h"

namespace math {

    class CalculatorImpl : public Calculator {
    public:

        
        virtual double add(double a, double b) {
            return a + b;
        }

        virtual double sub(double a, double b) {
            return add(a, -b);
        }
    };

} // math
