cmake_minimum_required(VERSION 3.21)
project(exercise3 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(exercise3
        BusTerminus.c
        BusTerminus.h
        main.c
        passenger.h
        queue.c
        queue.h
        stack.c
        stack.h)
