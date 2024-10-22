#pragma once

#include <cmath>

namespace real_numbers {
    template<class T> class my_numeric_limits {
    public:
       static constexpr T epsilon();
    };

    template<> class my_numeric_limits<long double> {
    public:
       static constexpr long double epsilon() { return 1e-11; };
       static constexpr long double min()     { return 1e-12; };
    };

    template<> class my_numeric_limits<double> {
    public:
       static constexpr double epsilon() { return 1e-9; };
       static constexpr double min()     { return 1e-10; };
    };

    template<> class my_numeric_limits<float> {
    public:
       static constexpr float epsilon() { return 1e-6; };
       static constexpr float min()     { return 1e-7; };
    };

    template <typename T = double>
    inline T get_normalized_eps(T a, T b) {
        return std::max(my_numeric_limits<T>::min(), std::max(a, b) * my_numeric_limits<T>::epsilon());
    }

    template <typename T = double>
    inline bool is_real_eq(T a, T b) noexcept {
        T eps = get_normalized_eps(a, b);
        return (std::fabs(a - b) < eps);
    }

    template <typename T = double>
    inline bool is_real_ne(T a, T b) noexcept {
        T eps = get_normalized_eps(a, b);
        return (std::fabs(a - b) > eps);
    }

    template <typename T = double>
    inline bool is_real_lt(T a, T b) noexcept {
        T eps = get_normalized_eps(a, b);
        return ((a - b) < -eps);
    }

    template <typename T = double>
    inline bool is_real_le(T a, T b) noexcept {
        T eps = get_normalized_eps(a, b);
        return ((a - b) < eps);
    }

    template <typename T = double>
    inline bool is_real_gt(T a, T b) noexcept {
        T eps = get_normalized_eps(a, b);
        return ((a - b) > eps);
    }

    template <typename T = double>
    inline bool is_real_ge(T a, T b) noexcept {
        T eps = get_normalized_eps(a, b);
        return ((a - b) > -eps);
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