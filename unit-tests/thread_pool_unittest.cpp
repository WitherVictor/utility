#include "gtest/gtest.h"

#include "thread_pool.hpp"

#include <type_traits>

template <typename T, typename U>
std::common_type_t<T, U> add(T first, U last) {
    return first + last;
}

template <typename T, typename U>
std::common_type_t<T, U> multiply(T first, U last) {
    return first * last;
}

TEST(thread_pool_unittest, basic_test) {
    std::size_t first = 3;
    std::size_t last = 5;
    std::size_t expected_result = 8;

    thread_pool pool{};
    auto add_task = [&first, &last]() { return add(first, last); };
    auto result = pool.submit(add_task);
    EXPECT_EQ(expected_result, result.get());

    expected_result = 15;
    auto multiply_task = [&first, &last]() { return multiply(first, last); };
    result = pool.submit(multiply_task);
    EXPECT_EQ(expected_result, result.get());
}