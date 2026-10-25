cmake_minimum_required(VERSION 4.1)
project(ProperitaererThreadPool)

set(CMAKE_CXX_STANDARD 17)

add_executable(ProperitaererThreadPool main.cpp)
target_include_directories(ProperitaererThreadPool PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
