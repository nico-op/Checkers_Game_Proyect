cmake_minimum_required(VERSION 3.23)
project(Projects_main)

set(SFML_STATIC_LIBRARIES TRUE)
set(CMAKE_CXX_STANDARD 14)


add_executable(checkersExe main.cpp)

add_executable(prueba PruebaWindow.cpp)

target_link_libraries(checkersExe sfml-system sfml-window sfml-graphics sfml-audio sfml-network)

target_link_libraries(prueba sfml-system sfml-window sfml-graphics sfml-audio sfml-network)
