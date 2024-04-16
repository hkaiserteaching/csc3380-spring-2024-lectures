cmake_minimum_required(VERSION 3.19)
project(spring2024-csc3380-lecture19)

set(CMAKE_CXX_STANDARD 20)

find_package(FLTK CONFIG QUIET)

if(FLTK_FOUND)
  set(fltk_targets fltk fltk_images)
else()
  include(FetchContent)
  
  FetchContent_Declare(FLTK
    GIT_REPOSITORY  https://github.com/fltk/fltk
    GIT_TAG         master
    GIT_SHALLOW     TRUE
  )
  
  FetchContent_MakeAvailable(FLTK)
  set(fltk_targets fltk::fltk fltk::images)
endif()

set(fltk_toolkit_sources
    code/Graph.cpp
    code/GUI.cpp
    code/Simple_window.cpp
    code/Window.cpp
)

add_executable(functions code/functions.cpp ${fltk_toolkit_sources})
target_link_libraries(functions PRIVATE ${fltk_targets})

add_executable(e_power_x code/e_power_x.cpp ${fltk_toolkit_sources})
target_link_libraries(e_power_x PRIVATE ${fltk_targets})
