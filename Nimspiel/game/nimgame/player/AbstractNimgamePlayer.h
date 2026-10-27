//
// Created by JoachimWagner on 27.10.2026.
//

#pragma once
#include <string>
#include "../../player/AbstractPlayer.h"

namespace game::nimgame::player {
    class AbstractNimgamePlayer :public game::player::AbstractPlayer<int,int>{
    public:
        explicit AbstractNimgamePlayer(const std::string &name)
           : AbstractPlayer<int, int>(name) {
        }
    };
}
