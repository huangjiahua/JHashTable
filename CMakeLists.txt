cmake_minimum_required(VERSION 3.12)
project(JHashTable)

set(CMAKE_CXX_STANDARD 14)

add_executable(JHashTable main.cpp)

add_subdirectory("./benchmark")