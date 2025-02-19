#include <print>

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
}