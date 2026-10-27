//
// Created by JoachimWagner on 27.10.2026.
//

#pragma once

#include <iostream>
#include <random>

#include "AbstractNimgamePlayer.h"

namespace game::nimgame::player {
    class GrandmaPlayer: public AbstractNimgamePlayer {
    public:
        using AbstractNimgamePlayer::AbstractNimgamePlayer;

        [[nodiscard]] auto makeTurn(const int &) const noexcept -> int override {
            static std::mt19937 generator{std::random_device{}()};
            std::uniform_int_distribution<int> distribution{1, 5};
            const int turn = distribution(generator);
            std::cout << this->getName() << " nimmt zufaellig " << turn << " Steine!" << std::endl;
            return turn;
        }
    };
}
