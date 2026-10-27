//
// Created by JoachimWagner on 27.10.2026.
//

#pragma once
#include <memory>
#include <vector>

#include "IGame.h"
#include "player/IPlayer.h"
#include "../io/IWriter.h"

namespace game {
    template<class BOARD, class MOVE>
    class AbstractGame :public IGame{

        using Player = player::IPlayer<BOARD, MOVE>;
        using PlayerPointer = std::unique_ptr<Player>;
        using Writer = std::unique_ptr<io::IWriter>;
    public:
        explicit AbstractGame(Writer writer)
            : writer_(std::move(writer)) {
        }

        auto play() noexcept -> void override{
            while (! isGameOver()) {
                playRound();
            }
        }

        auto addPlayer(PlayerPointer player) -> void { players_.push_back(std::move(player)); }


        auto removePlayer([[maybe_unused]]PlayerPointer player) -> void {
            // TODO implement later

        }



    private:
        std::vector<PlayerPointer> players_;
        BOARD board_;
        MOVE move_;

        Player *currentPlayer_{nullptr};

        Writer writer_;

        auto playRound() noexcept -> void {
            for (auto &player : players_) {
                setCurrentPlayer( player.get());
                playersTurn();
            }

        }

        auto playersTurn() noexcept -> void {

            if (isGameOver()) return;
            prepare();
            processPlayerTurn();
            terminateTurn( );
        }

        // Integration
        auto terminateTurn() noexcept -> void {
            updateBoard();
            displayLossMessage();
        }

        auto processPlayerTurn() noexcept-> void {

            do {
                askForMove();
            } while (!isTurnValid());

        }

        auto askForMove() noexcept -> void {
            setMove(getCurrentPlayer()->makeTurn(getBoard()));
            reportIfMoveInvalid();
        }

        // Operation
        auto displayLossMessage() const noexcept -> void {
            if (isGameOver()) {
                write(getCurrentPlayer()->getName() + " hat verloren");

            }
        }


        auto reportIfMoveInvalid() const noexcept -> void {
            if (! isTurnValid()) write ("Ungueltige Eingabe.") ;
        }

        auto setCurrentPlayer(Player *currentPlayer) -> void {
            currentPlayer_ = currentPlayer;
        }


    protected:

        virtual auto prepare() -> void {
            // Ok
        }

        [[nodiscard]]auto getPlayers() const -> const std::vector<PlayerPointer>& {
            return players_;
        }


        [[nodiscard]] auto getBoard() const -> const BOARD& {
            return board_;
        }

        auto getMove() const -> const MOVE& {
            return move_;
        }

        auto setBoard(const BOARD &board) -> void {
            board_ = board;
        }

        auto setMove(const MOVE &move) -> void {
            move_ = move;
        }

        auto write(const std::string &message) const  -> void {
            writer_->write(message);
        }


        [[nodiscard]] auto getCurrentPlayer() const -> Player * {
            return currentPlayer_;
        }

        [[nodiscard]] virtual auto isGameOver() const noexcept  -> bool = 0;
        virtual auto updateBoard()  noexcept -> void = 0;
        [[nodiscard]] virtual auto isTurnValid   () const noexcept -> bool = 0;

    };
}
