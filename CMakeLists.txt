cmake_minimum_required(VERSION 3.30)
project(AoC2024)

set(CMAKE_CXX_STANDARD 20)

include_directories(Source)
add_executable(AoC2024 Source/main.cpp
        Source/Helpers/AoCHelpers.cpp
        Source/Solutions/AoCSolution1.cpp
        Source/Solutions/AoCSolution2.cpp
        Source/Solutions/AoCSolution2.h
        Source/Solutions/AoCSolution3.cpp
        Source/Solutions/AoCSolution3.h
        Source/Solutions/AoCSolution4.cpp
        Source/Solutions/AoCSolution4.h
        Source/Solutions/AoCSolution5.cpp
        Source/Solutions/AoCSolution5.h
        Source/Solutions/AoCSolution6.cpp
        Source/Solutions/AoCSolution6.h
)

add_custom_command(
        TARGET AoC2024 POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/Input/*
        ${CMAKE_CURRENT_BINARY_DIR})

