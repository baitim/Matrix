cmake_minimum_required(VERSION 3.11)
project(matrix_src)

set(INCLUDE_DIR ../include)

add_executable(matrix matrix.cpp)
target_sources(matrix
    PRIVATE
    FILE_SET HEADERS
    BASE_DIRS ${INCLUDE_DIR}
)

# set(PYTHON_SCRIPT_GEN "${CMAKE_SOURCE_DIR}/tests/generate.py")
# add_test(
#     NAME generate_matrix_target
#     COMMAND bash -c "python3 ${PYTHON_SCRIPT_GEN}"
# )

add_library(Matrix matrix.cpp)
target_sources(Matrix
    PRIVATE
    FILE_SET HEADERS
    BASE_DIRS ${INCLUDE_DIR}
)
install(TARGETS Matrix)