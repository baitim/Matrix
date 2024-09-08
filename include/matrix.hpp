#pragma once

#include "ANSI_colors.hpp"

namespace matrix {
template <typename ElemT> class matrix_buf_t {
protected:
    int rows_;
    int cols_;
    ElemT* elems_;

    matrix_buf_t(int rows, int cols) : rows_(rows), cols_(cols) {
        elems_ = new ElemT[rows_ * cols_];
    }

    ~matrix_buf_t() {
        delete [] elems_;
    }
};

template <typename ElemT> class matrix_t final : private matrix_buf_t<ElemT> {
    using matrix_buf_t<ElemT>::rows_;
    using matrix_buf_t<ElemT>::cols_;
    using matrix_buf_t<ElemT>::elems_;

    struct ProxyRow final {
        ElemT* row;

        ElemT& operator[](int n) {
            return row[n];
        }

        ElemT operator[](int n) const {
            return row[n];
        }
    };

public:
    matrix_t(int rows, int cols) : matrix_buf_t<ElemT>(rows, cols) {}

    matrix_t(int rows, int cols, ElemT val) : matrix_t<ElemT>(rows, cols) {
        for (int i = 0, end = rows_ * cols_; i < end; ++i)
            elems_[i] = val;
    }

    template <typename It>
    matrix_t(int rows, int cols, It start, It fin) : matrix_t<ElemT>(rows, cols, 0) {
        int i = 0;
        int end = rows * cols;
        for (It it = start; it < fin && i < end; ++it, ++i)
            elems_[i] = *it;
    }

    static matrix_t<ElemT>* eye(int rows, int cols) {
        matrix_t<ElemT>* matrix = new matrix_t<ElemT>(rows, cols, 0);
        for (int i = 0, end = std::min(rows, cols); i < end; ++i)
            matrix->elems_[i * cols + i] = 1;
        return matrix;
    }

    ProxyRow& operator[](int n) {
        return ProxyRow{elems_ + n * cols_};
    }

    ProxyRow operator[](int n) const {
        return ProxyRow{elems_ + n * cols_};
    }

    int get_rows() const noexcept {
        return rows_;
    }

    int get_cols() const noexcept {
        return cols_;
    }

    ElemT trace() const noexcept {
        ElemT trace = 0;
        for (int i = 0, end = std::min(rows_, cols_); i < end; ++i)
            trace += elems_[i * cols_ + i];
        return trace;
    }

    bool swap_rows(int a, int b) noexcept {
        if (a == b)
            return false;

        int row_shift_a = a * cols_;
        int row_shift_b = b * cols_;
        for (int i = 0; i < rows_; i++)
            std::swap(elems_[row_shift_a + i], elems_[row_shift_b + i]);

        return true;
    }

    void simplify_rows(int i) {
        int row_shift_i = i * cols_;
        for (int j = i + 1; j < rows_; ++j) {

            int row_shift_j = j * cols_;
            double coef = elems_[row_shift_j + i] / elems_[row_shift_i + i];

            for (int k = 0; k < cols_; ++k)
                elems_[row_shift_j + k] -= coef * elems_[row_shift_i + k];
        }
    }

    double diag_mult() const noexcept {
        double det = 1;
        for (int i = 0, end = std::min(rows_, cols_); i < end; ++i)
            det *= elems_[i * cols_ + i];
        return det;
    }

    ElemT determinant() {
        if (cols_ != rows_)
            return 0;

        bool is_swapped = false;
        for (int i = 0; i < cols_; ++i) {

            int pivot = i;
            for (int j = i + 1; j < rows_; ++j) {
                int row_shift_j = j * cols_;
                if (abs(elems_[row_shift_j + i]) > abs(elems_[row_shift_j + pivot]))
                    pivot = j;
            }

            if (swap_rows(i, pivot))
                is_swapped = !is_swapped;
            
            if (elems_[i * cols_ + i] == 0)
                return 0;

            simplify_rows(i);
        }

        double det = diag_mult();
        if (is_swapped)
            det *= -1;

        return det;
    }
};

template <typename ElemT>
std::istream& operator>>(std::istream& is, const matrix_t<ElemT>& matrix) noexcept {
    int rows = matrix.get_rows();
    int cols = matrix.get_cols();

    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j)
            is >> matrix[i][j];
    return is;
}

template <typename ElemT>
std::ostream& operator<<(std::ostream& os, const matrix_t<ElemT>& matrix) noexcept {
    int rows = matrix.get_rows();
    int cols = matrix.get_cols();

    os << print_lblue("\nMatrix:\n");
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            os << print_lcyan(matrix[i][j]) << " ";
        }
        os << "\n";
    }
    os << "\n";
    return os;
}

};