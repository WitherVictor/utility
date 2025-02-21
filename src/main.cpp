#include <limits>
#include <print>
#include <generator>
#include <ranges>

#include "sqrt_newton.hpp"
#include "roll_dice.hpp"
#include "timer.hpp"
#include "thread_pool.hpp"

std::size_t calculate_add() {
    std::size_t result = 0;
    for (std::size_t i = 0; i < 100000; i++)
        result += i;

    return result;
}

std::size_t calculate_multiply() {
    std::size_t result = 1;
    for (std::size_t i = 1; i < 25; i++)
        result *= i;

    return result;
}

template <typename T>
std::generator<T> random_range(T begin, T end, std::size_t count = std::numeric_limits<std::size_t>::max()) {
    rng generator{begin, end};
    while (count-- > 0) 
        co_yield generator();

    co_return;
}

int main() {
    ::timer timer{};
    std::println("{}", roll_dice("6d6"));
    std::println("{}", sqrt_newton(3));
    std::println("Time elapsed : {}", timer.now());

    thread_pool pool{};
    auto add_future = pool.submit(calculate_add);
    auto multiply_future = pool.submit(calculate_multiply);
    std::println("Add result : {}", add_future.get());
    std::println("Multiply result : {}", multiply_future.get());

    for (auto i : random_range(1, 10) | std::views::take(10))
        std::println("Random numer: {}", i);
}