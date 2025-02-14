#include "gtest/gtest.h"

#include <cmath>

#include "sqrt_newton.hpp"

TEST(sqrt_newton_unittest, extreme_positive) {
    EXPECT_DOUBLE_EQ(sqrt_newton(1e30), 1e15);
}

TEST(sqrt_newton_unittest, golden_ratio) {
    EXPECT_DOUBLE_EQ(((1 + sqrt_newton(5)) / 2), 1.618033988749895);
}

TEST(sqrt_newton_unittest, decimal) {
    EXPECT_DOUBLE_EQ(sqrt_newton(0.5), 0.7071067811865476);
    EXPECT_DOUBLE_EQ(sqrt_newton(0.25), 0.5);
    EXPECT_DOUBLE_EQ(sqrt_newton(0.125), 0.3535533905932738);
    
}

TEST(sqrt_newton_unittest, trivial) {
    EXPECT_DOUBLE_EQ(sqrt_newton(1), 1.0);
    EXPECT_DOUBLE_EQ(sqrt_newton(2), 1.4142135623730951);
    EXPECT_DOUBLE_EQ(sqrt_newton(3), 1.7320508075688772);
    EXPECT_DOUBLE_EQ(sqrt_newton(5), 2.2360679774997900);
    EXPECT_DOUBLE_EQ(sqrt_newton(7), 2.6457513110645907);
}

TEST(sqrt_newton_unittest, zero) {
    EXPECT_DOUBLE_EQ(sqrt_newton(0), 0);
}

TEST(sqrt_newton_unittest, negative) {
    EXPECT_TRUE(std::isnan(sqrt_newton(-1)));
}