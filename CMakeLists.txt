cmake_minimum_required(VERSION 3.30)
project(AoC2024)

set(CMAKE_CXX_STANDARD 20)

include_directories(Source)
add_executable(AoC2024 Source/main.cpp
        Source/Helpers/AoCHelpers.cpp
        Source/Solutions/AoCSolution1.cpp
        Input/1.txt
        )

add_custom_command(
        TARGET AoC2024 POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/Input/*
        ${CMAKE_CURRENT_BINARY_DIR})

