cmake_minimum_required(VERSION 3.19)
project(spring2024-csc3380-lecture8)

set(CMAKE_CXX_STANDARD 20)

add_executable(test_singleton code/test_singleton.cpp)
add_executable(test_instrumented_unique 
    code/test_instrumented_unique.cpp 
    code/instrumented.cpp)
target_compile_definitions(
    test_instrumented_unique PRIVATE 
    CATCH_CONFIG_ENABLE_BENCHMARKING
    CATCH_CONFIG_RUNNER)
