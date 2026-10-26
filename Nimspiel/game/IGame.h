//
// Created by JoachimWagner on 26.10.2026.
//

#pragma once

namespace game {
    class IGame {
    public:
        virtual ~IGame() = default;
        virtual auto play() -> void= 0;

    };
}
