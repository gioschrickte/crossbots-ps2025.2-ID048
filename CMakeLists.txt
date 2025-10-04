cmake_minimum_required(VERSION 4.0)
project(crossbots_ps C)

set(CMAKE_C_STANDARD 11)

add_executable(crossbots_ps main.c
        blackjack.h
        blackjack.c
        )
