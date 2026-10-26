//
// Created by JoachimWagner on 26.10.2026.
//

#pragma once
#include <memory>

#include "../game/IGame.h"

namespace client {
    using Game = game::IGame;
    class Client {
    public:
        explicit Client(std::unique_ptr<Game> game)
            : game(std::move(game)) {
        }

        virtual ~Client() = default;
        auto go() -> void {
            game->play();
        }

    private:
        std::unique_ptr<Game> game;
    }; // client
}