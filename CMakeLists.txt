cmake_minimum_required(VERSION 3.9)
project(sem C)

set(CMAKE_C_STANDARD 90)

add_executable(sem main.c vector.c vector.h dfs.c dfs.h record.c record.h date.c date.h my-utils.c my-utils.h)