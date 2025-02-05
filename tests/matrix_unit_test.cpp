#include "Matrix/matrix.hpp"

#include <gtest/gtest.h>

#include <fstream>
#include <vector>
#include <algorithm>
#include <filesystem>
#include <fstream>

static const double EPSILON_ROUGH = 1e-3;
static const double EPSILON       = 1e-8;

std::vector<std::string> get_sorted_files(std::filesystem::path path) {
    std::vector<std::string> files;

    for (const auto& entry : std::filesystem::directory_iterator(path))
        files.push_back(entry.path().string());

    std::sort(files.begin(), files.end());
    return files;
}

TEST(Matrix_shuffle, end_to_end) 
{
    std::string file{__FILE__};
    std::filesystem::path dir = file.substr(0, file.rfind("/"));

    std::filesystem::path answers_path = dir / "answers/";
    std::filesystem::path tests_path   = dir / "tests_dat/";

    std::vector<std::string> answers_str = get_sorted_files(answers_path);
    std::vector<std::string> tests_str   = get_sorted_files(tests_path);
    const unsigned count_tests = std::min(answers_str.size(), tests_str.size());

    for (unsigned i = 0; i < count_tests; ++i) {
        std::ifstream test_file(tests_str[i]);
        unsigned n;
        test_file >> n;
        matrix::matrix_t<double> matrix{n, n};
        test_file >> matrix;
        test_file.close();

        std::ifstream answer_file(answers_str[i]);
        double ans;
        answer_file >> ans;
        answer_file.close();

        EXPECT_LT(std::fabs(matrix.determinant() - ans), EPSILON_ROUGH);
    }
}

TEST(Matrix_main, test_fill_val)
{
    unsigned n = 3;
    float val = 52;
    matrix::matrix_t<float> matrix{n, n, val};

    ASSERT_LT(std::fabs(matrix.determinant()), EPSILON);
}

TEST(Matrix_main, test_trace)
{
    unsigned n = 3;
    std::vector<double> elems{1e0, 1e1, 1e2,
                              1e3, 1e4, 1e5,
                              1e6, 1e7, 1e8};

    matrix::matrix_t<double> matrix{n, n, elems.begin(), elems.end()};

    ASSERT_LT(std::fabs(matrix.trace() - (1e0 + 1e4 + 1e8)), EPSILON);
}

TEST(Matrix_main, test_eye)
{
    unsigned n = 52;
    matrix::matrix_t<double> matrix = matrix::matrix_t<double>::eye(n, n, 0.f, 1.f);

    ASSERT_LT(std::fabs(matrix.determinant() - 1), EPSILON);
    ASSERT_LT(std::fabs(matrix.trace() - n), EPSILON);
}

TEST(Matrix_main, test_int3)
{
    unsigned n = 3;
    std::vector<int> elems{11, 7,  13,
                           17, 19, 6,
                           7,  8,  9};

    matrix::matrix_t<int> matrix{n, n, elems.begin(), elems.end()};

    ASSERT_LT(std::fabs(matrix.determinant() - 615), EPSILON);

    std::vector<int> elems2{31, 37, 13,
                            19, 11, 7,
                            43, 41, 3};

    matrix::matrix_t<int> matrix2{n, n, elems2.begin(), elems2.end()};

    ASSERT_LT(std::fabs(matrix2.determinant() - 5132), EPSILON);
}

TEST(Matrix_main, test_int4)
{
    unsigned n = 4;
    std::vector<int> elems{31, 37, 13, 67,
                           43, 41, 7,  93,
                           13, 11, 3,  91,
                           51, 53, 71, 73};

    matrix::matrix_t<int> matrix{n, n, elems.begin(), elems.end()};

    ASSERT_LT(std::fabs(matrix.determinant() - 1195792), EPSILON);
}

TEST(Matrix_mult, test_ints)
{
    unsigned n = 4;
    unsigned m = 3;
    unsigned k = 5;

    std::vector<int> elems1{1,  3,  7,
                            11, 13, 17,
                            19, 23, 29,
                            31, 37, 41};

    std::vector<int> elems2{2, 9, 15, 19, 21,
                            6, 7, 12, 11, 37,
                            5, 3, 51, 17, 33};

    std::vector<int> elems3{55,  51,  408,  171,  363,
                            185, 241, 1188, 641,  1273,
                            321, 419, 2040, 1107, 2207,
                            489, 661, 3000, 1693, 3373};

    matrix::matrix_t<int> matrix1{n, m, elems1.begin(), elems1.end()};
    matrix::matrix_t<int> matrix2{m, k, elems2.begin(), elems2.end()};
    matrix::matrix_t<int> matrix3{n, k, elems3.begin(), elems3.end()};

    ASSERT_EQ(matrix1 * matrix2, matrix3);
}

TEST(Matrix_det, test_double)
{
    unsigned n = 3;
    std::vector<double> elems{1.6, 1.9, 0.5,
                              1.1, 1.3, 0.8,
                              0.3, 0.4, 0.5};

    matrix::matrix_t<double> matrix{n, n, elems.begin(), elems.end()};

    ASSERT_LT(std::fabs(matrix.determinant() - (-0.036)), EPSILON);
}

TEST(Matrix_det, test_long_double)
{
    unsigned n1 = 4;
    long double default_value = 15;
    matrix::matrix_t<long double> matrix1{n1, n1, default_value};

    unsigned n2 = 3;
    std::vector<long double> elems{7, 13, 3,
                                   4, 5,  17,
                                   9, 11, 10};

    matrix::matrix_t<long double> matrix2{n2, n2, elems.begin(), elems.end()};
    ASSERT_LT(std::fabs(matrix1.determinant() - 0), EPSILON);
    ASSERT_LT(std::fabs(matrix2.determinant() - 507), EPSILON);
}

TEST(Matrix_det, test_rectangle)
{
    unsigned n = 2, m = 3;
    std::vector<double> elems{1.3, 1.2, 0.7,
                              1.4, 1.6, 0.4};

    matrix::matrix_t<double> matrix{n, m, elems.begin(), elems.end()};

    ASSERT_LT(std::fabs(matrix.determinant() - 0), EPSILON);
}

TEST(Matrix_det, test_det_cleanness)
{
    unsigned n = 3;
    std::vector<double> elems{1.4, 2.1, 0.5,
                              1.6, 0.8, 1.7,
                              0.9, 1.2, 1.8};

    matrix::matrix_t<double> matrix{n, n, elems.begin(), elems.end()};
    matrix::matrix_t<double> matrix2 = matrix;

    ASSERT_LT(std::fabs(matrix.determinant() - (-3.075)), EPSILON);
    ASSERT_EQ((matrix == matrix2), 1);
}

TEST(Matrix_det, test1)
{
    unsigned n = 4;
    std::vector<float> elems{0, 0,  0, -1,
                             0, 0, -1,  0,
                             0, 1,  0,  0,
                             1, 0,  0,  0};

    matrix::matrix_t<float> matrix{n, n, elems.begin(), elems.end()};
    ASSERT_LT(std::fabs(matrix.determinant() - 1), EPSILON);
}

TEST(Matrix_raii, test_copy_assign_ctor)
{
    unsigned n = 2;
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
    unsigned n1 = 2;
    double default_value = 52;
    matrix::matrix_t<double> matrix1{n1, n1, default_value};
    std::vector<double> elems{1.4, 2.1, 0.5,
                              1.6, 0.8, 1.7,
                              0.9, 1.2, 1.8};

    unsigned n2 = 3;
    matrix::matrix_t<double> matrix2{n2, n2, elems.begin(), elems.end()};

    std::swap(matrix1, matrix2);

    ASSERT_LT(std::fabs(matrix1.determinant() - (-3.075)), EPSILON);
    ASSERT_LT(std::fabs(matrix2.determinant() - 0), EPSILON);
}

int main(int argc, char **argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}