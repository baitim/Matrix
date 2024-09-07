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

    matrix::matrix_t<double> matrix{n, n, elems.begin(), elems.end()};

    ASSERT_LT(abs(matrix.determinant() - (-0.036)), EPSILON);
}

TEST(Matrix_main, test_fill_val)
{
    int n = 3;
    double val = 42;
    matrix::matrix_t<double> matrix{n, n, val};

    ASSERT_LT(abs(matrix.determinant() - 0), EPSILON);
}

TEST(Matrix_main, test_trace)
{
    int n = 3;
    std::vector<double> elems{1e0, 1e1, 1e2,
                              1e3, 1e4, 1e5,
                              1e6, 1e7, 1e8};

    matrix::matrix_t<double> matrix{n, n, elems.begin(), elems.end()};

    ASSERT_LT(abs(matrix.trace() - (1e0 + 1e4 + 1e8)), EPSILON);
}

TEST(Matrix_main, test_eye)
{
    int n = 333;
    matrix::matrix_t<double>* matrix = matrix::matrix_t<double>::eye(n, n);

    EXPECT_LT(abs(matrix->determinant() - 1), EPSILON);
    EXPECT_LT(abs(matrix->trace() - n), EPSILON);
    delete matrix;
}