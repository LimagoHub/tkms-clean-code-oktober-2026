//
// Created by JoachimWagner on 01.12.2025.
//

#pragma once
#include <iostream>
#include <memory>
#include "../math/Calculator.h"


namespace client {

    class Client {

        std::unique_ptr<math::Calculator> calculator;

    public:

        explicit Client(std::unique_ptr<math::Calculator> calculator) : calculator(std::move(calculator)) {}
        void go() {
            std::cout << calculator->add(3,4) << "\n";
        }

    };

} // client
