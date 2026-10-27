//
// Created by JoachimWagner on 20.01.2026.
//

#pragma once

#include <string>

namespace game::player {
    template<class BOARD, class TURN>
    class IPlayer {
    public:
        virtual ~IPlayer() = default;
        virtual auto getName() const  -> const std::string = 0;
        virtual auto makeTurn(const BOARD &board) const -> TURN = 0;
    };

} // player
