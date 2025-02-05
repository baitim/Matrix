#pragma once

#include <cmath>

namespace real_numbers {
    template<class T> class my_numeric_limits {
    public:
       static constexpr T epsilon();
    };

    template<> class my_numeric_limits<long double> {
    public:
       static constexpr long double epsilon() { return 1e-12; };
    };

    template<> class my_numeric_limits<double> {
    public:
       static constexpr double epsilon() { return 1e-9; };
    };

    template<> class my_numeric_limits<float> {
    public:
       static constexpr float epsilon() { return 1e-6; };
    };

    template <typename T = double>
    inline T get_max_abs(T a, T b) noexcept {
        return std::max(std::abs(a), std::abs(b));
    }

    template <typename T = double>
    inline bool is_real_eq(T a, T b) noexcept {
        T max_abs = get_max_abs(a, b);
        if (max_abs < std::numeric_limits<T>::epsilon())
            return true;

        T eps = my_numeric_limits<T>::epsilon();
        return ((std::fabs(a - b) / max_abs) < eps);
    }

    template <typename T = double>
    inline bool is_real_ne(T a, T b) noexcept {
        T max_abs = get_max_abs(a, b);
        if (max_abs < std::numeric_limits<T>::epsilon())
            return false;

        T eps = my_numeric_limits<T>::epsilon();
        return ((std::fabs(a - b) / max_abs) > eps);
    }

    template <typename T = double>
    inline bool is_real_lt(T a, T b) noexcept {
        T max_abs = get_max_abs(a, b);
        if (max_abs < std::numeric_limits<T>::epsilon())
            return false;

        T eps = my_numeric_limits<T>::epsilon();
        return (((a - b) / max_abs) < -eps);
    }

    template <typename T = double>
    inline bool is_real_le(T a, T b) noexcept {
        T max_abs = get_max_abs(a, b);
        if (max_abs < std::numeric_limits<T>::epsilon())
            return true;

        T eps = my_numeric_limits<T>::epsilon();
        return (((a - b) / max_abs) < eps);
    }

    template <typename T = double>
    inline bool is_real_gt(T a, T b) noexcept {
        T max_abs = get_max_abs(a, b);
        if (max_abs < std::numeric_limits<T>::epsilon())
            return false;

        T eps = my_numeric_limits<T>::epsilon();
        return (((a - b) / max_abs) > eps);
    }

    template <typename T = double>
    inline bool is_real_ge(T a, T b) noexcept {
        T max_abs = get_max_abs(a, b);
        if (max_abs < std::numeric_limits<T>::epsilon())
            return true;

        T eps = my_numeric_limits<T>::epsilon();
        return (((a - b) / max_abs) > -eps);
    }

    template <typename T = double>
    inline bool is_real_in_range(T a, T b, T c) noexcept {
        if (is_real_le(a, b) && is_real_ge(a, c))
            return true;

        if (is_real_le(a, c) && is_real_ge(a, b))
            return true;

        return false;
    }
}