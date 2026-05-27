#include "numeric\newton.hpp"
#include "geometric\geom.hpp"

numeric::NewtonResult project_point_on_line_newton(
    const geom::Vec3& P0,
    const geom::Vec3& v,
    const geom::Vec3& Q,
    double t0) {
    const auto func = [P0, v, Q](double t) {
        const geom::Vec3 point = P0 + v * t;
        return (point - Q).dot(v);
        };

    const double vv = v.dot(v);
    const auto deriv = [vv](double) {
        return vv;
        };

    return numeric::newton_solve(func, deriv, t0);
}