cmake_minimum_required(VERSION 3.10)
project(schpliterator)
add_library(spliterator INTERFACE)
target_include_directories(spliterator INTERFACE "${CMAKE_CURRENT_LIST_DIR}/include")

