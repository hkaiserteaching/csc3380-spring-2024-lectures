cmake_minimum_required(VERSION 3.19)
project(spring2024-csc3380-lecture20)

set(CMAKE_CXX_STANDARD 20)

add_executable(bf_interpreter code/bf_interpreter_ref.cpp)
add_executable(bf_compiler code/bf_compiler.cpp)
add_executable(bf_optimizing_compiler code/bf_optimizing_compiler_ref.cpp)
add_executable(bf_code code/bf_code.cpp)
