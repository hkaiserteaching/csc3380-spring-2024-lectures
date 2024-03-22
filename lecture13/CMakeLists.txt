cmake_minimum_required(VERSION 3.19)
project(spring2024-csc3380-lecture13)

set(CMAKE_CXX_STANDARD 20)

add_executable(counting_words code/counting_words.cpp)
add_executable(splitting_lines code/splitting_lines.cpp)
add_executable(cross_reference code/cross_reference.cpp)
add_executable(generating_sentences code/generating_sentences.cpp)
