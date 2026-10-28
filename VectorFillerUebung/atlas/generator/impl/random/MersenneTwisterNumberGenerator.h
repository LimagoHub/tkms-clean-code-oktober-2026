//
// Created by JoachimWagner on 30.06.2023.
//

#pragma once
#include <random>
#include <climits>
#include "../../IIntGenerator.h"

namespace atlas::generator {

    class MersenneTwisterNumberGenerator : public IIntGenerator {
    public:
        ~MersenneTwisterNumberGenerator() override = default;

        explicit MersenneTwisterNumberGenerator()
            : rng_{std::random_device{}()} {}

        [[nodiscard]] auto next() noexcept -> int override {
            return distribution_(rng_);
        }

    private:
        std::mt19937 rng_;
        std::uniform_int_distribution<std::int32_t> distribution_{INT_MIN, INT_MAX};
    };

}
