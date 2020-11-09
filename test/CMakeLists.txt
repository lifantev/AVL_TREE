cmake_minimum_required(VERSION 3.15)

project(AvlTest VERSION 0.0.1)

add_executable(AvlTreeTest
    AvlTreeTest.cpp 
    ${CMAKE_CURRENT_SOURCE_DIR}/../AvlTree.hpp
)

target_link_libraries(AvlTreeTest PUBLIC
    gtest_main
)

add_test(
    NAME AvlTreeTest
    COMMAND AvlTreeTest
)