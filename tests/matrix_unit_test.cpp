#include <fstream>
#include <vector>
#include <algorithm>
#include <glob.h>
#include <gtest/gtest.h>
#include "matrix.hpp"

static const double EPSILON_ROUGH = 1e-3;
static const double EPSILON       = 1e-8;

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

        EXPECT_LT(std::fabs(matrix.determinant() - ans), EPSILON_ROUGH);
    }

    globfree(&test_files);
    globfree(&ans_files);
}

TEST(Matrix_main, test_fill_val)
{
    int n = 3;
    double val = 52;
    matrix::matrix_t<double> matrix{n, n, val};

    ASSERT_LT(std::fabs(matrix.determinant() - 0), EPSILON);
}

TEST(Matrix_main, test_trace)
{
    int n = 3;
    std::vector<double> elems{1e0, 1e1, 1e2,
                              1e3, 1e4, 1e5,
                              1e6, 1e7, 1e8};

    matrix::matrix_t<double> matrix{n, n, elems.begin(), elems.end()};

    ASSERT_LT(std::fabs(matrix.trace() - (1e0 + 1e4 + 1e8)), EPSILON);
}

TEST(Matrix_main, test_eye)
{
    int n = 52;
    matrix::matrix_t<double>* matrix = matrix::matrix_t<double>::eye(n, n);

    EXPECT_LT(std::fabs(matrix->determinant() - 1), EPSILON);
    EXPECT_LT(std::fabs(matrix->trace() - n), EPSILON);
    delete matrix;
}

TEST(Matrix_det, test_double)
{
    int n = 3;
    std::vector<double> elems{1.6, 1.9, 0.5,
                              1.1, 1.3, 0.8,
                              0.3, 0.4, 0.5};

    matrix::matrix_t<double> matrix{n, n, elems.begin(), elems.end()};

    ASSERT_LT(std::fabs(matrix.determinant() - (-0.036)), EPSILON);
}

TEST(Matrix_det, test_int)
{
    int n1 = 4;
    int default_value = 15;
    matrix::matrix_t<int> matrix1{n1, n1, default_value};

    int n2 = 3;
    std::vector<int> elems{7, 13, 3,
                           4, 5,  17,
                           9, 11, 10};

    matrix::matrix_t<int> matrix2{n2, n2, elems.begin(), elems.end()};
    ASSERT_LT(std::fabs(matrix1.determinant() - 0), EPSILON);
    ASSERT_LT(std::fabs(matrix2.determinant() - 507), EPSILON);
}

TEST(Matrix_det, test_rectangle)
{
    int n = 2, m = 3;
    std::vector<double> elems{1.3, 1.2, 0.7,
                              1.4, 1.6, 0.4};

    matrix::matrix_t<double> matrix{n, m, elems.begin(), elems.end()};

    ASSERT_LT(std::fabs(matrix.determinant() - 0), EPSILON);
}

TEST(Matrix_det, test_det_cleanness)
{
    int n = 3;
    std::vector<double> elems{1.4, 2.1, 0.5,
                              1.6, 0.8, 1.7,
                              0.9, 1.2, 1.8};

    matrix::matrix_t<double> matrix{n, n, elems.begin(), elems.end()};
    matrix::matrix_t<double> matrix2 = matrix;

    ASSERT_LT(std::fabs(matrix.determinant() - (-3.075)), EPSILON);
    ASSERT_EQ((matrix == matrix2), 1);
}

TEST(Matrix_raii, test_copy_assign_ctor)
{
    int n = 2;
    double default_value = 52;
    matrix::matrix_t<double> matrix{n, n, default_value};

    if (1) {
        n = 3;
        std::vector<double> elems{1.4, 2.1, 0.5,
                                  1.6, 0.8, 1.7,
                                  0.9, 1.2, 1.8};

        matrix::matrix_t<double> matrix2{n, n, elems.begin(), elems.end()};
        matrix = matrix2;
    }

    ASSERT_LT(std::fabs(matrix.determinant() - (-3.075)), EPSILON);
}

TEST(Matrix_raii, test_move_assign_ctor)
{
    int n1 = 2;
    double default_value = 52;
    matrix::matrix_t<double> matrix1{n1, n1, default_value};
    std::vector<double> elems{1.4, 2.1, 0.5,
                              1.6, 0.8, 1.7,
                              0.9, 1.2, 1.8};

    int n2 = 3;
    matrix::matrix_t<double> matrix2{n2, n2, elems.begin(), elems.end()};

    matrix::swap(matrix1, matrix2);

    ASSERT_LT(std::fabs(matrix1.determinant() - (-3.075)), EPSILON);
    ASSERT_LT(std::fabs(matrix2.determinant() - 0), EPSILON);
}