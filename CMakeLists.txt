cmake_minimum_required(VERSION 3.23)
project(Projects_main)

set(CMAKE_CXX_STANDARD 14)

add_executable(Projects_main
        "CHIP-8 Emulator/main.cpp"
        "Conway's Game of Life/main.cpp"
        "Double Pendulum/main.cpp"
        "Insertion Sort Visualization/main.cpp")


add_executable(checkersExe Checkers/main.cpp)
target_link_libraries(checkersExe sfml-system sfml-window sfml-graphics)

