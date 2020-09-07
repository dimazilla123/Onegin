cmake_minimum_required(VERSION 3.1)

project(onegin)
include_directories(src include)

set(SRC 
    src/main.c
    src/algorithm.c
    src/string_utils.c
    src/vector.c
    )

add_executable(sort ${SRC})
add_executable(test_vector src/test_vector.c src/vector.c)
target_link_libraries(test_vector)
target_link_libraries(sort m)