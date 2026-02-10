#include <gtest/gtest.h>

#include <rng.hpp>

TEST(rng_unittest, integer_test) {
    auto r1{rng(0, 100)};
    for ([[maybe_unused]] const auto _ : std::views::iota(0, 100)) {
        auto val{r1()};

        EXPECT_GE(val, 0);
        EXPECT_LE(val, 100);
    }
}

TEST(rng_unittest, float_test) {
    auto r1{rng(0.0, 100.0)};
    for ([[maybe_unused]] const auto _ : std::views::iota(0, 100)) {
        auto val{r1()};

        EXPECT_GE(val, 0.0);
        EXPECT_LE(val, 100.0);
    }
}

TEST(rng_unittest, exception_test) {
    EXPECT_NO_THROW(rng(0, 100));
    EXPECT_NO_THROW(rng(20, 20));

    EXPECT_THROW(rng(100, 0), std::invalid_argument);
}