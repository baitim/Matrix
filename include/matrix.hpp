#pragma once

#include "ANSI_colors.hpp"
#include "real_numbers.hpp"

#include <iostream>
#include <cstring>
#include <type_traits>

namespace matrix {
    template <typename ElemT> class matrix_buf_t {
    protected:
        int rows_;
        int cols_;
        ElemT* elems_; // less news &
                       // number of elems in row is constant &
                       // can precalculate shift of rows index like shift_i = i * N, then m[shift_i + j]

        matrix_buf_t(int rows, int cols) : rows_(rows), cols_(cols) {
            static_assert(std::is_default_constructible_v<ElemT>, "Type must be default-constructible");
            elems_ = new ElemT[rows_ * cols_]{};
        }

        matrix_buf_t(const matrix_buf_t<ElemT>& other) : matrix_buf_t<ElemT>(other.rows_, other.cols_) {
            static_assert(std::is_assignable_v<ElemT&, ElemT>, "Type must be assignable");
            for (int i = 0, end = rows_ * cols_; i < end; ++i)
                elems_[i] = other.elems_[i];
        }

        matrix_buf_t& operator=(const matrix_buf_t<ElemT>& other) {
            if (this == &other)
                return *this;

            matrix_buf_t<ElemT> new_matrix_buf{other};
            std::swap(rows_,  new_matrix_buf.rows_);
            std::swap(cols_,  new_matrix_buf.cols_);
            std::swap(elems_, new_matrix_buf.elems_);
            return *this;
        }

        matrix_buf_t(matrix_buf_t<ElemT>&& other) noexcept : rows_(other.rows_), cols_(other.cols_), 
                                                             elems_(other.elems_) {
            other.rows_ = other.cols_ = 0;
            other.elems_ = nullptr;
        }
        
        matrix_buf_t& operator=(matrix_buf_t<ElemT>&& other) noexcept {
            if (this == &other)
                return *this;

            std::swap(rows_,  other.rows_);
            std::swap(cols_,  other.cols_);
            std::swap(elems_, other.elems_);
            return *this;
        }

        ~matrix_buf_t() {
            for (int i = 0, end = rows_ * cols_; i < end; ++i)
                 elems_[i].~ElemT();
            delete [] elems_;
        }
    };

    template <typename ElemT>
    class matrix_t;

    template <typename ElemT>
    bool swap_rows(matrix_t<ElemT>& matrix, int a, int b) noexcept;

    template <typename ElemT>
    class matrix_t final : private matrix_buf_t<ElemT> {
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

    private:
        void   simplify_rows(matrix_t<double>& calc_matrix, int i);
        double diag_mult    (const matrix_t<double>& calc_matrix) const noexcept;

    public:
        matrix_t(int rows, int cols) : matrix_buf_t<ElemT>(rows, cols) {}

        matrix_t(int rows, int cols, const ElemT& val) : matrix_t<ElemT>(rows, cols) {
            static_assert(std::is_assignable_v<ElemT&, ElemT>, "Type must be assignable");
            for (int i = 0, end = rows_ * cols_; i < end; ++i)
                elems_[i] = val;
        }

        template <typename It>
        matrix_t(int rows, int cols, It start, It fin) : matrix_t<ElemT>(rows, cols) {
            static_assert(std::is_assignable_v<ElemT&, typename It::value_type>, "Type must be assignable");
            int i = 0;
            int end = rows * cols;
            for (It it = start; it < fin && i < end; ++it, ++i)
                elems_[i] = *it;
        }

        static matrix_t<ElemT> eye(int rows, int cols, const ElemT& zero, const ElemT& one) {
            static_assert(std::is_assignable_v<ElemT&, ElemT>, "Type must be assignable");
            matrix_t<ElemT> matrix{rows, cols, zero};
            for (int i = 0, end = std::min(rows, cols); i < end; ++i)
                matrix.elems_[i * cols + i] = one;
            return matrix;
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

        template <typename ElemT2>
        matrix_t(const matrix_t<ElemT2>& other) : matrix_buf_t<ElemT>(other.get_rows(), other.get_cols()) {
            static_assert(std::is_assignable_v<ElemT&, ElemT2>, "Type must be assignable");
            for(int i = 0; i < rows_; ++i) {
                int row_shift_i = i * cols_;
                for (int j = 0; j < cols_; ++j) {
                    elems_[row_shift_i + j] = other[i][j];
                }
            }
        }

        ElemT trace() const noexcept {
            ElemT trace = 0;
            for (int i = 0, end = std::min(rows_, cols_); i < end; ++i)
                trace += elems_[i * cols_ + i];
            return trace;
        }

        double determinant() {
            if (cols_ != rows_)
                return 0;

            matrix_t<double> calc_matrix{*this};

            bool is_swapped = false;
            for (int i = 0; i < cols_; ++i) {

                int pivot = i;
                for (int j = i + 1; j < rows_; ++j) {
                    if (real_numbers::is_real_gt((double)fabs(calc_matrix[j][i]),
                                                 (double)fabs(calc_matrix[pivot][i])))
                        pivot = j;
                }

                if (swap_rows(calc_matrix, i, pivot))
                    is_swapped = !is_swapped;

                if (real_numbers::is_real_eq(calc_matrix[i][i], (double)0))
                    return 0;

                simplify_rows(calc_matrix, i);
            }

            double det = diag_mult(calc_matrix);
            if (is_swapped)
                det *= -1;

            return det;
        }
    };

    template <typename ElemT>
    bool swap_rows(matrix_t<ElemT>& matrix, int a, int b) noexcept {
        if (a == b)
            return false;

        int cols = matrix.get_cols();
        for (int i = 0; i < cols; i++)
            std::swap(matrix[a][i], matrix[b][i]);

        return true;
    }

    template <typename ElemT>
    void matrix_t<ElemT>::simplify_rows(matrix_t<double>& calc_matrix, int i) {
        int rows = calc_matrix.get_rows();
        int cols = calc_matrix.get_cols();

        for (int j = i + 1; j < rows; ++j) {
            double coef = calc_matrix[j][i] / calc_matrix[i][i];
            for (int k = 0; k < cols; ++k)
                calc_matrix[j][k] -= coef * calc_matrix[i][k];
        }
    }

    template <typename ElemT>
    double matrix_t<ElemT>::diag_mult(const matrix_t<double>& calc_matrix) const noexcept {
        int rows = calc_matrix.get_rows();
        int cols = calc_matrix.get_cols();
        if (rows != cols)
            return 0;

        double det = 1;
        for (int i = 0; i < rows; ++i)
            det *= calc_matrix[i][i];
        return det;
    }

    template <typename ElemT>
    bool operator==(const matrix_t<ElemT>& x, const matrix_t<ElemT>& y) noexcept {
        int xrows = x.get_rows();
        int xcols = x.get_cols();
        int yrows = y.get_rows();
        int ycols = y.get_cols();

        if ((xrows != yrows) || (xcols != ycols))
            return false;

        for (int i = 0; i < xrows; i++)
            for (int j = 0; j < xcols; j++)
                if (x[i][j] != y[i][j])
                    return false;

        return true;
    }

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