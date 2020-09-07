cmake_minimum_required(VERSION 3.1)

project(onegin)
include_directories(src include)

set(SRC 
    src/main.c
    src/algorithm.c
    src/string_utils.c
    )

add_executable(sort ${SRC})
target_link_libraries(sort m)