#include "gtest/gtest.h"

#include "rng.hpp"

TEST(rng_unittest, basic_test) {
    rng r1{0, 100};
    auto v1 = r1();

    EXPECT_GE(v1, 0);
    EXPECT_LT(v1, 100);
}

TEST(rng_unittest, exception_test) {
    EXPECT_NO_THROW(rng(0, 100));
    EXPECT_NO_THROW(rng(20, 20));

    EXPECT_THROW(rng(100, 0), std::invalid_argument);
}