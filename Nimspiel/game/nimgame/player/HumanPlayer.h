//
// Created by JoachimWagner on 27.10.2026.
//

#pragma once
#include <iostream>

#include "AbstractNimgamePlayer.h"

namespace game::nimgame::player {
    class HumanPlayer: public AbstractNimgamePlayer {
    public:
        using AbstractNimgamePlayer::AbstractNimgamePlayer;

        [[nodiscard]] auto makeTurn(const int &stones) const noexcept -> int override {
            int turn;
            std::cout << "Es gibt " << stones << " Steine. Bitte nehmen Sie 1, 2 oder 3!\n";
            std::cin >> turn;
            return turn;
        }
    };
}
