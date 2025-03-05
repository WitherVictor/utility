#include "gtest/gtest.h"

#include "gcd.hpp"

TEST(gcd_unittest, basic_test) {
    EXPECT_EQ(gcd(18, 24), 6);
    EXPECT_EQ(gcd(54, 72), 18);
    EXPECT_EQ(gcd(600, 125), 25);
}

TEST(gcd_unittest, one_arg_zero) {
    EXPECT_EQ(gcd(42, 0), 42);
    EXPECT_EQ(gcd(0, 72), 72);
}

TEST(gcd_unittest, all_arg_zero) {
    EXPECT_EQ(gcd(0, 0), 0);
}