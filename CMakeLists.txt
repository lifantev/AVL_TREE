cmake_minimum_required(VERSION 3.15)

project(AvlTree VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 17)

enable_testing()

add_subdirectory(googletest)
add_subdirectory(test)
