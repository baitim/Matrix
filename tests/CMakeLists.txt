cmake_minimum_required(VERSION 3.11)
project(tests)

set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

find_package(GTest REQUIRED)

add_executable(unit_matrix matrix_unit_test.cpp)
target_include_directories(unit_matrix PUBLIC ${INCLUDE_DIR})
target_link_libraries(unit_matrix gtest::gtest)

set(RUN_TESTS ./unit_matrix --gtest_color=yes)
add_test(
    NAME unit_matrix_target
    COMMAND ${RUN_TESTS}
)