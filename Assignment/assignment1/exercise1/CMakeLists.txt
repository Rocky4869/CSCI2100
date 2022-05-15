cmake_minimum_required(VERSION 3.21)
project(exercise1 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(exercise1
        main.c
        stack.c
        stack.h)
