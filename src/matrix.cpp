#include <iostream>
#include <iomanip>
#include <vector>
#include "matrix.hpp"

int main() {

    int n;
    std::cin >> n;

    matrix::matrix_t<double> matrix{n, n};
    std::cin >> matrix;

    std::cout << std::fixed << std::setprecision(10) << matrix.determinant() << "\n";
    return 0;
}