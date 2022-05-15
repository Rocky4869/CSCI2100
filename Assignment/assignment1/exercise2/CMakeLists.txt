cmake_minimum_required(VERSION 3.21)
project(exercise2 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(exercise2
        main.c
        stack.c
        stack.h)
