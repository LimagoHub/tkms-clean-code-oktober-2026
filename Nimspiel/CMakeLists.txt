cmake_minimum_required(VERSION 4.3)
project(Nimspiel)

set(CMAKE_CXX_STANDARD 17)

add_executable(Nimspiel main.cpp
        game/IGame.h
        client/GameClient.h
        game/nimgame/Nimgame.h
        game/nimgame/player/AbstractNimgamePlayer.h
        game/nimgame/player/HumanPlayer.h
        game/nimgame/player/ComputerPlayer.h
        io/ConsoleWriter.h
        game/player/IPlayer.h
        game/player/AbstractPlayer.h
        game/AbstractGame.h
)
