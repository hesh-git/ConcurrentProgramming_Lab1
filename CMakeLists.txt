cmake_minimum_required(VERSION 3.26)
project(ConcurrentProgramming_Lab1 C)

set(CMAKE_C_STANDARD 23)

add_executable(ConcurrentProgramming_Lab1 main.c linkedlist.c
        serial.c
        serial.h
        global.c
        global.h
        rwlock.c
        rwlock.h)
