//
// Created by JoachimWagner on 26.10.2026.
//

#pragma once
#include "../IGame.h"

namespace game::nimgame {
    class Nimgame : public IGame{

    public:
        Nimgame(){
            stones = 23;

        }
        auto play() noexcept -> void override{
            while (! isGameOver()) {
                playTurn();
            }
        }

    private:
        int stones;
        int turn{0};

        auto playTurn() noexcept -> void {
            playerTurn();
            computerTurn();
        }

        auto playerTurn() noexcept -> void {

            if (isGameOver()) return;


            while (true) {
                std::cout << "Es gibt " << stones << " Steine. Bitte nehmen Sie 1,2 oder 3 Steine: ";
                std::cin >> turn;
                if (turn >= 1 && turn <= 3)break;
                std::cout << "Ungueltige Eingabe." << std::endl;

            }
            terminateTurn( "Spieler");
        }



        auto computerTurn() noexcept -> void {
            if (isGameOver()) return;


            const int zuege[] = {3,1,1,2};
            turn = zuege[stones % 4];
            std::cout << "Der Computer nimmt " << turn << " Steine." << std::endl;



            terminateTurn( "Computer");
        }




        // Integration
        void terminateTurn( std::string message) {
            updateBoard();
            display_loss_message(message);
        }


        // Operation
        void display_loss_message(std::string message) {
            if (isGameOver()) {
                std::cout << message << " hat verloren" << std::endl;
            }
        }
// ----- Impementierungssumpf --------------------------

        void updateBoard() {
            stones -= turn;
        }


        auto isGameOver() const noexcept -> bool {
            return stones < 1;
        }
    };
}
