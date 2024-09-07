#include <iostream>
#include <vector>
#include "matrix.hpp"

int main() {

    int n;
    std::cin >> n;
    std::vector<double> elems(n * n);

    for (int i = 0; i < n * n; ++i) {
        std::cin >> elems[i];
    }

    matrix::matrix_t<double> matrix{n, elems};

    std::cout << matrix.det() << "\n";

    return 0;
}