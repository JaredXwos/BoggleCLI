cmake_minimum_required(VERSION 3.29)
project(BoggleCLI C)

set(CMAKE_C_STANDARD 11)

# Include the resource in your executable
add_executable(BoggleCLI tripletquizzer.c
        tripletquizzer.h
        main.c
        speedpuzzler.c
        speedpuzzler.h
        puzzlerinit.c)