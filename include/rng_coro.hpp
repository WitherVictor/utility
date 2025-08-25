#include <algorithm>
#include <array>
#include <stdexcept>
#include <random>
#include <stdexcept>
#include <type_traits>
#include <generator>

template <typename T, typename engine_type = std::mt19937_64>
requires std::is_arithmetic_v<T>
std::generator<T> rng(T left, T right) {
    if (left > right)
        throw std::invalid_argument{ "The left bound of rng should be smaller than right bound."};

    //  generate random seeds
    std::random_device rd{};
    std::array<std::random_device::result_type, engine_type::state_size> seed_data{};
    std::ranges::generate(seed_data, [&rd]() { return rd(); });

    std::seed_seq seeds{seed_data.begin(), seed_data.end()};
    engine_type engine{seeds};

    //  generate range according to type T is integer or floating point
    auto range = [&left, &right]() {
        if constexpr (std::is_integral_v<T>) {
            return std::uniform_int_distribution<T>{left, right};
        } else if constexpr (std::is_floating_point_v<T>) {
            return std::uniform_real_distribution<T>{left, right};
        } else {
            static_assert(false, "T is not arithmetic type which is impossible.");
        }
    }();

    while (true) {
        co_yield range(engine);
    }
}