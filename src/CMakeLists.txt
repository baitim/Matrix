cmake_minimum_required(VERSION 3.11)
project(matrix_src)

set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

add_executable(matrix matrix.cpp)
target_include_directories(matrix PUBLIC ${INCLUDE_DIR})