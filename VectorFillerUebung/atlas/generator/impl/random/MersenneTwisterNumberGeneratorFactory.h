//
// Created by JoachimWagner on 30.06.2023.
//

#pragma once
#include "../../IGeneratorFactory.h"
#include "MersenneTwisterNumberGenerator.h"

namespace atlas::generator {

    class MersenneTwisterNumberGeneratorFactory : public IGeneratorFactory<int> {
    public:
        ~MersenneTwisterNumberGeneratorFactory() override = default;

        [[nodiscard]] auto create() const -> std::unique_ptr<IGenerator<int>> override {
            return std::make_unique<MersenneTwisterNumberGenerator>();
        }
    };

}
