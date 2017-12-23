cmake_minimum_required(VERSION 3.9)
project(sem C)

set(CMAKE_C_STANDARD 90)

add_executable(sem main.c dfs.h)