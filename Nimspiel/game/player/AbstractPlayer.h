//
// Created by JoachimWagner on 20.01.2026.
//

#pragma once
#include <string>
#include <typeinfo>
#include <cstring>
#include "IPlayer.h"

namespace game::player {

    template<class BOARD, class TURN>
    class AbstractPlayer : public IPlayer<BOARD, TURN> {
    public:

        explicit AbstractPlayer(const std::string &name) : name_(name) {}

        ~AbstractPlayer() override = default;

        auto getName() const -> const std::string override {
            return name_;
        }

    private:
        std::string name_;


    };

} // player
