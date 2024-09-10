#pragma once

#include <cmath>

namespace doubles {
    const double EPSILON = 1e-8;
    
    bool is_double_equal(double a, double b) noexcept {
        return (std::fabs(a - b) < EPSILON);
    }

    bool is_double_greater(double a, double b) noexcept {
        return ((a - b) > EPSILON);
    }

    bool is_double_less(double a, double b) noexcept {
        return ((a - b) < EPSILON);
    }
}