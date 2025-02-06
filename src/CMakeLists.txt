cmake_minimum_required(VERSION 3.11)
project(matrix_src)

set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

add_executable(matrix matrix.cpp)
target_sources(matrix
    PRIVATE
    FILE_SET HEADERS
    BASE_DIRS ${INCLUDE_DIR}
)

add_library(Matrix matrix.cpp)
target_include_directories(Matrix PUBLIC
    $<BUILD_INTERFACE:${INCLUDE_DIR}>
    $<INSTALL_INTERFACE:include>
)

install(TARGETS Matrix EXPORT MatrixTargets
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include
)

install(DIRECTORY ${INCLUDE_DIR}/Matrix DESTINATION include)

install(EXPORT MatrixTargets
    FILE MatrixConfig.cmake
    DESTINATION lib/cmake/Matrix
)