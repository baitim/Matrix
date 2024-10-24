#include "matrix.hpp"

int main() {

    int n;
    std::cin >> n;

    if (!std::cin.good() || n <= 0) {
        std::cout << print_red("Incorrect input matrix size\n");
        return 1;
    }

    unsigned matrix_size = n;
    matrix::matrix_t<double> matrix{matrix_size, matrix_size};

    try {
        std::cin >> matrix;
    } catch (const char* error_message) {
        std::cout << print_red(error_message) << "\n";
        return 1;
    }

    std::cout << matrix.determinant() << "\n";
    return 0;
}