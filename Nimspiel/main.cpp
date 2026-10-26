#include <iostream>

#include "client/GameClient.h"
#include "game/nimgame/Nimgame.h"
#include "game/IGame.h"

using NimGame = game::nimgame::Nimgame;
using GameClient = client::Client;
using Game = game::IGame;

int main() {
    std::unique_ptr<Game> game = std::make_unique<NimGame>();

    client::Client client{std::move(game)};

    client.go();
    return 0;
}
