//
// Created by JoachimWagner on 10.04.2024.
//

#pragma once
#include "IGenerator.h"
namespace atlas::generator {
    class IIntGenerator : public IGenerator<int>{
    public:
        ~IIntGenerator() override = default;
    };
}

