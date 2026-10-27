#include <iostream>

#include "client/GameClient.h"
#include "game/nimgame/Nimgame.h"
#include "game/IGame.h"
#include "game/nimgame/player/HumanPlayer.h"
#include "game/nimgame/player/ComputerPlayer.h"
#include "io/ConsoleWriter.h"

using NimGame = game::nimgame::Nimgame;
using GameClient = client::Client;
using Game = game::IGame;
using HumanPlayer = game::nimgame::player::HumanPlayer;
using ComputerPlayer = game::nimgame::player::ComputerPlayer;
using Writer = io::ConsoleWriter;

int main() {

    auto writer = std::make_unique<Writer>();
    auto human = std::make_unique<HumanPlayer>("Horst");
    auto computer = std::make_unique<ComputerPlayer>("HAL");


    auto game = std::make_unique<NimGame>(std::move(writer));
    game->addPlayer(std::move(human));
    game->addPlayer(std::move(computer));

    client::Client client{std::move(game)};

    client.go();
    return 0;
}
