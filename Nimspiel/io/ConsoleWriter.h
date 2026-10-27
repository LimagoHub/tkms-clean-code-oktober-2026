//
// Created by JoachimWagner on 20.01.2026.
//

#pragma once
#include <iostream>
#include "IWriter.h"
namespace io {

    class ConsoleWriter :public IWriter{
    public:
        ~ConsoleWriter() override = default;

        auto write(const std::string &message) const -> void override {
            std::cout << message << std::endl;
        }
    };

} // io
