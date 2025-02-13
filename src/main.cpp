#include <print>

#include "sqrt_newton.hpp"
#include "roll_dice.hpp"
#include "timer.hpp"

int main() {
    ::timer timer{};
    std::println("{}", roll_dice("6d6"));
    std::println("{}", sqrt_newton(3));
    std::println("Time elapsed : {}", timer.now());
}