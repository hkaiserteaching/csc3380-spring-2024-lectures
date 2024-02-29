cmake_minimum_required(VERSION 3.19)
project(spring2024-csc3380-lecture9)

set(CMAKE_CXX_STANDARD 20)

add_executable(fibonacci code/fibonacci.cpp)

add_executable(generic_multiply code/multiply.cpp)
add_executable(power code/power.cpp)
add_executable(generic_power code/generic_power.cpp)

add_executable(fibonacci_logn code/fibonacci_logn.cpp)
add_executable(fibonacci_benchmark code/fibonacci_benchmark.cpp)
target_compile_definitions(
    fibonacci_benchmark PRIVATE 
    CATCH_CONFIG_ENABLE_BENCHMARKING
    CATCH_CONFIG_MAIN)

add_executable(fibonacci_instrumented
    code/fibonacci_instrumented.cpp
    code/instrumented.cpp)
