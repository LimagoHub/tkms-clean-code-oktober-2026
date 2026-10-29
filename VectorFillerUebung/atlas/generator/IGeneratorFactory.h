//
// Created by JoachimWagner on 11.04.2024.
//

#pragma once
#include <memory>
#include "IGenerator.h"

namespace atlas::generator {

    template<class T>
    class IGeneratorFactory {
    public:
        virtual ~IGeneratorFactory() = default;
        [[nodiscard]] virtual auto create() const -> std::unique_ptr<IGenerator<T>> = 0;
    };

}
