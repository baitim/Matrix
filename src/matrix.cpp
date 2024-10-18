#include "matrix.hpp"

int main() {

    int n;
    std::cin >> n;

    matrix::matrix_t<double> matrix{n, n};
    std::cin >> matrix;

    std::cout << matrix.determinant() << "\n";
    return 0;
}