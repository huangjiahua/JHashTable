cmake_minimum_required(VERSION 3.12)
project(JHashTable)

set(CMAKE_CXX_STANDARD 14)

add_executable(JHashTable main.cpp src/JHashBucket.h include/JHashTable.h)

add_subdirectory("./benchmark")


# Debug session
add_executable(BucketDebug test/BucketTest1.cpp src/JHashHeader.h)
add_executable(HashTableTest test/HashTableTest1.cpp include/JHashTable.h)
