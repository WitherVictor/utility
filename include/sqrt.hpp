#pragma once

#include <cmath>
#include <limits>

long double sqrt_newton(long double init_value) {
    if (init_value < 0)
        return std::numeric_limits<long double>::quiet_NaN();

    if (init_value == 0)
        return 0;

    long double init_solution = 1;
    while (true) {
        //  x_n+1 = x_n - f(x_n) / f'(x_n)
        //
        //  f(x) = x^2 - n  解为 x = √￣n
        //  f'(x) = 2 * x
        //
        //  ∴ x - f(x) / f'(x) = (x + n / x) / 2
        long double next_solution = (init_solution + init_value / init_solution) / 2;
        if (std::abs(next_solution - init_solution) < std::numeric_limits<long double>::epsilon())
            break;

        init_solution = next_solution;
    }

    return init_solution;
}