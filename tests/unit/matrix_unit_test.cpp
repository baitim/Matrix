#include <vector>
#include <gtest/gtest.h>
#include "matrix.hpp"

const double EPSILON = 1e-8;

TEST(Matrix_main, test_double)
{
    int n = 3;
    std::vector<double> elems{1.6, 1.9, 0.5,
                              1.1, 1.3, 0.8,
                              0.3, 0.4, 0.5};

    matrix::matrix_t<double> matrix{n, elems};

    ASSERT_LT(abs(matrix.det() - (-0.036)), EPSILON);
}