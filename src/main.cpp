#include <roll_dice.hpp>
#include <timer.hpp>
#include <print>

int main() {
    ::timer timer{};
    std::println("{}", roll_dice("6d6"));
    std::println("Time elapsed : {}", timer.now());
}