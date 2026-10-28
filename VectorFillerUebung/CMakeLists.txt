cmake_minimum_required(VERSION 4.3)
project(VectorFillerUebung)

set(CMAKE_CXX_STANDARD 17)

add_executable(VectorFillerUebung main.cpp
        atlas/generator/IGenerator.h
        atlas/time/IStopwatch.h
        atlas/client/IClient.h
        atlas/client/impl/ClientImpl.h)
