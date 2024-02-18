cmake_minimum_required(VERSION 3.19)
project(spring2024-csc3380-lecture10)

set(CMAKE_CXX_STANDARD 20)

add_executable(frame_images code/frame_images.cpp)
add_executable(vcat_images code/vcat_images.cpp)
add_executable(hcat_images code/hcat_images.cpp)
add_executable(vflip_images code/vflip_images.cpp)
add_executable(rotate_left_images code/rotate_left_images.cpp)
add_executable(working_with_queues code/working_with_queues.cpp)
