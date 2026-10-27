//
// Created by JoachimWagner on 26.10.2026.
//

#pragma once
#include <iostream>
#include <string>
#include "../IGame.h"

namespace game::nimgame {
    class Nimgame : public IGame{

    public:
        Nimgame() noexcept {
            stones_ = 23;

        }
        auto play() noexcept -> void override{
            while (! isGameOver()) {
                playTurn();
            }
        }

    private:
        int stones_;
        int turn_{0};

        auto playTurn() noexcept -> void {
            playersTurn();
            computerTurn();
        }



        auto playersTurn() noexcept -> void {

            if (isGameOver()) return;
            processPlayerTurn();
            terminateTurn( "Spieler");
        }

        auto processPlayerTurn() noexcept-> void {

            do {
                askForMove();
            } while (!isTurnValid());

        }

        auto askForMove() noexcept -> void {
            concretePlayerTurn();
            reportIfMoveInvalid();
        }

        auto concretePlayerTurn() noexcept -> void {
            std::cout << "Es gibt " << stones_ << " Steine. Bitte nehmen Sie 1,2 oder 3 Steine: ";
            std::cin >> turn_;
        }

        auto reportIfMoveInvalid() const noexcept -> void {
            if (! isTurnValid()) std::cout << "Ungueltige Eingabe." << std::endl;
        }



        auto computerTurn() noexcept -> void {
            if (isGameOver()) return;


            const int zuege[] = {3,1,1,2};
            turn_ = zuege[stones_ % 4];
            std::cout << "Der Computer nimmt " << turn_ << " Steine." << std::endl;



            terminateTurn( "Computer");
        }




        // Integration
        auto terminateTurn(const std::string& message) noexcept -> void {
            updateBoard();
            displayLossMessage(message);
        }


        // Operation
        auto displayLossMessage(const std::string& message) const noexcept -> void {
            if (isGameOver()) {
                std::cout << message << " hat verloren" << std::endl;
            }
        }
// ----- Implementierungssumpf --------------------------

        auto updateBoard() noexcept -> void {
            stones_ -= turn_;
        }


        auto isGameOver() const noexcept -> bool {
            return stones_ < 1;
        }

        auto isTurnValid() const noexcept -> bool {
            return turn_ >= 1 && turn_ <= 3;
        }
    };
}
