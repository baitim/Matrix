#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <glob.h>
#include <gtest/gtest.h>
#include "matrix.hpp"

const double EPSILON_ROUGH = 1e-3;
const double EPSILON = 1e-8;

TEST(Matrix_shuffle, end_to_end) 
{
    glob_t test_files;
    glob("../../tests/tests_dat/test_*.in", GLOB_ERR, NULL, &test_files);

    glob_t ans_files;
    glob("../../tests/answers/answer_*.ans", GLOB_ERR, NULL, &ans_files);

    int count_tests = std::min(test_files.gl_pathc, ans_files.gl_pathc);
    for (int i = 0; i < count_tests; ++i) {
        std::ifstream test_file(test_files.gl_pathv[i]);
        int n;
        test_file >> n;
        matrix::matrix_t<double> matrix{n, n};
        test_file >> matrix;
        test_file.close();

        std::ifstream answer_file(ans_files.gl_pathv[i]);
        double ans;
        answer_file >> ans;
        answer_file.close();

        EXPECT_LT(abs(matrix.determinant() - ans), EPSILON_ROUGH);
    }

    globfree(&test_files);
    globfree(&ans_files);
}

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
    double val = 52;
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
    int n = 52;
    matrix::matrix_t<double>* matrix = matrix::matrix_t<double>::eye(n, n);

    EXPECT_LT(abs(matrix->determinant() - 1), EPSILON);
    EXPECT_LT(abs(matrix->trace() - n), EPSILON);
    delete matrix;
}