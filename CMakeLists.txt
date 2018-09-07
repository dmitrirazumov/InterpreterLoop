cmake_minimum_required(VERSION 3.10)
project(Loop C)

set(CMAKE_C_STANDARD 99)

add_executable(Loop executor.c headers/executor.h expressions.c headers/expressions.h loader.c headers/loader.h
        loop.c headers/loop.h tokenReader.c headers/tokenReader.h utilities.c headers/utilities.h variables.c
        headers/variables.h)