//
// Created by JoachimWagner on 27.10.2026.
//

#pragma once


#include <iostream>

#include "AbstractNimgamePlayer.h"

namespace game::nimgame::player {
    class ComputerPlayer: public AbstractNimgamePlayer {
    public:
        using AbstractNimgamePlayer::AbstractNimgamePlayer;

        [[nodiscard]] auto makeTurn(const int &stones) const noexcept -> int override {
            const int turn = optimalMoves[stones % 4];
            std::cout << this->getName() << " nimmt " << turn << " Steine!" << std::endl;
            return turn;
        }

    private:
        static inline const int optimalMoves[] = {3,1,1,2};
    };
}
