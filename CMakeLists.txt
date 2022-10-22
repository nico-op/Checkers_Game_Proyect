cmake_minimum_required(VERSION 3.23)
project(Projects_main)

set(CMAKE_CXX_STANDARD 14)
add_executable(checkersExe main.cpp)
target_link_libraries(checkersExe sfml-system sfml-window sfml-graphics)

