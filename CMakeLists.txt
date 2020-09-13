cmake_minimum_required(VERSION 3.1)

set(CMAKE_C_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address")
set(CMAKE_LINKER_FLAGS_DEBUG "${CMAKE_LINKER_FLAGS_DEBUG}  -fsanitize=address")

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
add_executable(test_string_utils src/test_string_utils.c src/string_utils.c src/vector.c)
add_executable(test_algorithms src/test_algorithm.c src/algorithm.c src/string_utils.c src/vector.c)
target_link_libraries(test_vector)
target_link_libraries(sort m)
