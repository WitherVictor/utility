#include <gtest/gtest.h>

#include <rng_coro.hpp>

#include <stdexcept>

TEST(rng_coro_unittest, integer_test) {
    for (const auto& value : rng(0, 100) | std::views::take(1000)) {
        EXPECT_GE(value, 0);
        EXPECT_LE(value, 100);
    }
}

TEST(rng_coro_unittest, float_test) {
    for (const auto& value : rng(0.0f, 1.0f) | std::views::take(1000)) {
        EXPECT_GE(value, 0.0f);
        EXPECT_LE(value, 1.0f);
    }
}

TEST(rng_coro_unittest, exception_test) {
    EXPECT_THROW(for (const auto& _ : rng(100, 0) | std::views::take(1000)) {}, std::invalid_argument);
    EXPECT_THROW(for (const auto& _ : rng(100.0, 0.0) | std::views::take(1000)) {}, std::invalid_argument);
}