#include <cmath>
#include <gtest/gtest.h>

#include "geometric/geom.hpp"
#include "numeric/newton.hpp"


numeric::NewtonResult project_point_on_line_newton(
    const geom::Vec3& P0,
    const geom::Vec3& v,
    const geom::Vec3& Q,
    double t0 = 0.0);

TEST(NewtonSolve, QuadraticRoot) {
    const auto f = [](double x) {
        return x * x - 2.0;
        };
    const auto df = [](double x) {
        return 2.0 * x;
        };

    const numeric::NewtonResult result = numeric::newton_solve(f, df, 1.0);
    EXPECT_TRUE(result.converged);
    EXPECT_NEAR(std::sqrt(2.0), result.root, 1e-8);
}


TEST(NewtonSolve, NegativeRoot) { 
    const auto f = [](double x) { 
        return x * x - 9.0; 
        }; 
    const auto df = [](double x) {
        return 2.0 * x; 
        }; 
    const numeric::NewtonResult result = 
        numeric::newton_solve(f, df, -5.0); 

    EXPECT_TRUE(result.converged); 
    EXPECT_NEAR(-3.0, result.root, 1e-8); 
}


TEST(NewtonSolve, NumericDerivativeQuadratic) { 
    const auto f = [](double x) {
        return x * x - 25.0; 
        }; 
    const numeric::NewtonResult result =
        numeric::newton_solve_numeric_deriv(f, 3.0); 
    
    EXPECT_TRUE(result.converged); 
    EXPECT_NEAR(5.0, result.root, 1e-6); 
}

TEST(NewtonSolve, FarInitialGuess) { 
    const auto f = [](double x) { 
        return x * x - 16.0; 
        }; 
    const auto df = [](double x) {
        return 2.0 * x; 
        }; 
    const numeric::NewtonResult result = 
        numeric::newton_solve(f, df, 100.0); 
    
    EXPECT_TRUE(result.converged); 
    EXPECT_NEAR(4.0, result.root, 1e-8); 
}


TEST(NewtonSolve, CosineIntersection) {
    const auto f = [](double x) {
        return std::cos(x) - x;
        };
    const numeric::NewtonResult result =
        numeric::newton_solve_numeric_deriv(f, 0.5);

    EXPECT_TRUE(result.converged);
    EXPECT_NEAR(0.7390851332151607, result.root, 1e-8);
}

TEST(NewtonSolve, SmallDerivativeFailsToConverge) {
    const auto f = [](double) {
        return 1.0;
        };
    const auto df = [](double) {
        return 0.0;
        };

    const numeric::NewtonResult result = numeric::newton_solve(f, df, 0.0);
    EXPECT_FALSE(result.converged);
    EXPECT_EQ(0, result.iterations);
}

TEST(GeometryNewton, PointAlreadyOnLine) { 
    geom::Vec3 P0{ 0.0, 0.0, 0.0 }; 
    geom::Vec3 v{ 1.0, 0.0, 0.0 }; 
    geom::Vec3 Q{ 5.0, 0.0, 0.0 }; 

    numeric::NewtonResult res = project_point_on_line_newton(P0, v, Q, 0.0); 

    EXPECT_TRUE(res.converged); 
    EXPECT_NEAR(5.0, res.root, 1e-10); 
}


TEST(GeometryNewton, ProjectPointOnLine_XAxis) {
    geom::Vec3 P0{ 0.0, 0.0, 0.0 };
    geom::Vec3 v{ 1.0, 0.0, 0.0 };

    geom::Vec3 Q{ 2.0, 3.0, 0.0 };

    numeric::NewtonResult res = project_point_on_line_newton(P0, v, Q, 0.0);
    EXPECT_TRUE(res.converged);
    EXPECT_NEAR(res.root, 2.0, 1e-10);

    geom::Vec3 proj = P0 + v * res.root;
    EXPECT_NEAR(proj.x, 2.0, 1e-10);
    EXPECT_NEAR(proj.y, 0.0, 1e-10);
    EXPECT_NEAR(proj.z, 0.0, 1e-10);
}

TEST(GeometryNewton, DiagonalLineProjection) { 
    geom::Vec3 P0{ 0.0, 0.0, 0.0 }; 
    geom::Vec3 v{ 1.0, 1.0, 0.0 }; 
    geom::Vec3 Q{ 2.0, 0.0, 0.0 }; 
    
    numeric::NewtonResult res = project_point_on_line_newton(P0, v, Q, 0.0); 
    EXPECT_TRUE(res.converged); 
    
    geom::Vec3 proj = P0 + v * res.root; 
    EXPECT_NEAR(proj.x, 1.0, 1e-8); 
    EXPECT_NEAR(proj.y, 1.0, 1e-8); 
    EXPECT_NEAR(proj.z, 0.0, 1e-8); 
}

TEST(GeometryNewton, NegativeDirectionVector) { 
    geom::Vec3 P0{ 0.0, 0.0, 0.0 }; 
    geom::Vec3 v{ -1.0, 0.0, 0.0 }; 
    geom::Vec3 Q{ 3.0, 2.0, 0.0 }; 
    
    numeric::NewtonResult res = project_point_on_line_newton(P0, v, Q, 0.0); 
    
    EXPECT_TRUE(res.converged); 
    EXPECT_NEAR(-3.0, res.root, 1e-10); 
}

