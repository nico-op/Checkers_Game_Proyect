# Must declare a path variable "SFML_ROOT" which points to .../.../SFML-2.1 top-level directory

cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
# ENABLE CMP0054: Only interpret if() arguments as variables or keywords when unquoted
cmake_policy(SET CMP0054 NEW)
# ENABLE CMP0074: USE *_ROOT PATH variables
cmake_policy(SET CMP0074 NEW)

# Meta information about the project
set(META_PROJECT_NAME        "Checkers")
set(META_PROJECT_DESCRIPTION "Play a game of checkers with a computer")
set(META_AUTHOR_ORGANIZATION "Flunkies")
set(META_AUTHOR_DOMAIN       "https://github.com/zmertens/checkers")
set(META_AUTHOR_MAINTAINER   "zmertens@mailinator.com")
set(META_VERSION_MAJOR       "2")
set(META_VERSION_MINOR       "0")
set(META_VERSION_PATCH       "0")
#set(META_VERSION_REVISION    "<REVISION>")
set(META_VERSION             "${META_VERSION_MAJOR}.${META_VERSION_MINOR}.${META_VERSION_PATCH}")
#set(META_NAME_VERSION        "${META_PROJECT_NAME} v${META_VERSION} (${META_VERSION_REVISION})")
set(META_CMAKE_INIT_SHA      "<CMAKE_INIT_REVISION>")

string(MAKE_C_IDENTIFIER ${META_PROJECT_NAME} META_PROJECT_ID)
string(TOUPPER ${META_PROJECT_ID} META_PROJECT_ID)
message(${META_PROJECT_NAME} " " ${META_PROJECT_ID})

# Require C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_BUILD_TYPE RelWithDebInfo)

project("Checkers" LANGUAGES CXX)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake_modules")

# Detect and add SFML
find_package(SFML 2.2 REQUIRED system window graphics audio)
include_directories(${SFML_INCLUDE_DIR})
message(${SFML_LIBRARIES})

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
    message(FATAL_ERROR "Do not build in-source. Please remove CMakeCache.txt and the CMakeFiles/ directory. Then build out-of-source.")
endif()

file(
    GLOB_RECURSE
    source_files
    src/*
)

add_executable(Checkers ${source_files})

target_link_libraries(Checkers ${SFML_LIBRARIES})
