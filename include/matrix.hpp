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

        const ElemT& operator[](int n) const {
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

    ElemT determinant() const {
        for (int i = 0; i < rows_; ++i) {
            for (int j = i + 1; j < cols_; ++j) {
                double coef = elems_[i * cols_ + j] / elems_[i * cols_ + i];

                for (int k = 0; k < rows_; k++) {
                    elems_[k * cols_ + j] -= coef * elems_[k * cols_ + i];
                }
            }
        }

        double ans = 1;
        for (int i = 0; i < rows_; ++i)
            ans *= elems_[i * cols_ + i];
            
        return ans;
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