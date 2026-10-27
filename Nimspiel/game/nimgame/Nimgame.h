//
// Created by JoachimWagner on 26.10.2026.
//

#pragma once
#include <iostream>
#include <string>
#include <memory>
#include <vector>

#include "../../io/IWriter.h"
#include "../AbstractGame.h"


namespace game::nimgame {
    class Nimgame : public AbstractGame<int,int>{
        using Writer = std::unique_ptr<io::IWriter>;

    public:
        Nimgame(Writer writer): AbstractGame(std::move(writer)) {
            setBoard(23);

        }

// ----- Implementierungssumpf --------------------------

    protected:
        auto isGameOver() const noexcept -> bool override {
            return getBoard() < 1 || getPlayers().empty();
        }

        auto updateBoard()  noexcept -> void override {
            setBoard(getBoard() - getMove());
        }

        auto isTurnValid() const noexcept -> bool override {
            return getMove() >= 1 && getMove() <= 3;
        }
        auto prepare() -> void override {
            write(getCurrentPlayer()->getName() + " ist am Zug");
        }

    };
}
