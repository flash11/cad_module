#pragma once

#include <cmath>

namespace numeric {

    struct NewtonResult {
        double root;
        int iterations;
        bool converged;
    };

    namespace detail {
        static constexpr double DF_EPS = 1e-14;
        static constexpr double NUM_DERIV_H = 1e-6;
    }

    template <typename F, typename DF>
    inline NewtonResult newton_solve(
        F f,
        DF df,
        double x0,
        int max_iters = 50,
        double tol = 1e-10
    ) {
        using namespace detail;

        NewtonResult result{ x0, 0, false };

        double x = x0;

        for (int iter = 0; iter < max_iters; ++iter) {

            const double fx = f(x);
            const double dfx = df(x);


            if (!std::isfinite(fx) || !std::isfinite(dfx)) {
                result.root = x;
                result.iterations = iter;
                result.converged = false;
                return result;
            }


            if (std::abs(dfx) < DF_EPS) {
                result.root = x;
                result.iterations = iter;
                result.converged = std::abs(fx) <= tol;
                return result;
            }

            const double step = fx / dfx;
            const double next = x - step;


            if (std::abs(step) <= tol || std::abs(fx) <= tol) {
                result.root = next;
                result.iterations = iter + 1;
                result.converged = true;
                return result;
            }

            x = next;
        }

        result.root = x;
        result.iterations = max_iters;
        result.converged = std::abs(f(x)) <= tol;

        return result;
    }

    template <typename F>
    inline double numeric_derivative(F f, double x, double h = detail::NUM_DERIV_H) {
        const double forward = f(x + h);
        const double backward = f(x - h);
        return (forward - backward) / (2.0 * h);
    }

    template <typename F>
    inline NewtonResult newton_solve_numeric_deriv(
        F f,
        double x0,
        int max_iters = 50,
        double tol = 1e-10
    ) {
        using namespace detail;

        NewtonResult result{ x0, 0, false };

        double x = x0;

        for (int iter = 0; iter < max_iters; ++iter) {

            const double fx = f(x);
            const double dfx = numeric_derivative(f, x);

            if (!std::isfinite(fx) || !std::isfinite(dfx)) {
                result.root = x;
                result.iterations = iter;
                result.converged = false;
                return result;
            }

            if (std::abs(dfx) < DF_EPS) {
                result.root = x;
                result.iterations = iter;
                result.converged = std::abs(fx) <= tol;
                return result;
            }

            const double step = fx / dfx;
            const double next = x - step;

            if (std::abs(step) <= tol || std::abs(fx) <= tol) {
                result.root = next;
                result.iterations = iter + 1;
                result.converged = true;
                return result;
            }

            x = next;
        }

        result.root = x;
        result.iterations = max_iters;
        result.converged = std::abs(f(x)) <= tol;

        return result;
    }

}