cmake_minimum_required(VERSION 3.11)
project(tests)

set(INCLUDE_DIR ../include)

find_package(GTest REQUIRED)

add_executable(unit_matrix matrix_unit_test.cpp)
target_sources(unit_matrix
    PRIVATE
    FILE_SET HEADERS
    BASE_DIRS ${INCLUDE_DIR}
)
target_link_libraries(unit_matrix PRIVATE GTest::GTest)

set(RUN_TESTS ./unit_matrix --gtest_color=yes)
add_test(
    NAME unit_matrix_target
    COMMAND ${RUN_TESTS}
)