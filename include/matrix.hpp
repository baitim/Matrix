#pragma once

#include "ANSI_colors.hpp"

namespace matrix {
template <typename ElemT> class matrix_t final {
    int rows_;
    int cols_;
    ElemT** elems_;

public:
    matrix_t(int size, const std::vector<ElemT>& elems) : rows_(size), cols_(size) {
        elems_ = new ElemT*[rows_];
        for (int i = 0; i < rows_; ++i) {
            elems_[i] = new ElemT[cols_];

            int shift = i * cols_;
            for (int j = 0; j < cols_; ++j) {
                elems_[i][j] = elems[shift + j];
            }
        }
    }

    ElemT det() {
        for (int i = 0; i < rows_; ++i) {
            for (int j = i + 1; j < cols_; ++j) {
                double coef = elems_[i][j] / elems_[i][i];

                for (int k = 0; k < rows_; k++) {
                    elems_[k][j] -= coef * elems_[k][i];
                }
            }
        }

        double ans = 1;
        for (int i = 0; i < rows_; ++i)
            ans *= elems_[i][i];
            
        return ans;
    }

    void print() {
        std::cout << print_lblue("\nMatrix:\n");
        for (int i = 0; i < rows_; ++i) {
            for (int j = 0; j < cols_; ++j) {
                std::cout << print_lcyan(elems_[i][j]) << " ";
            }
            std::cout << "\n";
        }
    }

    ~matrix_t() {
        for(int i = 0; i < rows_; ++i)
            delete [] elems_[i];
        delete [] elems_;
    }
};
};