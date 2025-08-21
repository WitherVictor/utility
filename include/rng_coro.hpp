#include <algorithm>
#include <array>
#include <coroutine>
#include <exception>
#include <random>
#include <stdexcept>
#include <type_traits>

#if __cplusplus < 202302L || !__cpp_lib_generator

template <typename T>
struct generator {
    struct promise_type {
        auto initial_suspend() { return std::suspend_always{}; }
        auto final_suspend() noexcept { return std::suspend_never{}; }
        auto return_void() {}
        auto unhandled_exception() { return std::terminate(); }
        auto get_return_object() {
            return generator{
                std::coroutine_handle<promise_type>::from_promise(*this)
            };
        }

        auto yield_value(T&& value) {
            current_value = value;
            return std::suspend_always{};
        }

        T current_value;
    };

    std::coroutine_handle<promise_type> handle;

    auto yield() {
        handle.resume();
        return handle.promise().current_value;
    }
};

#else

#include <generator>

#endif

template <typename T, typename engine_type = std::mt19937_64>
requires std::is_arithmetic_v<T>
#if __cplusplus < 202302L || !__cpp_lib_generator
generator<T>
#else
std::generator<T>
#endif
rng(T left, T right) {
    if (left > right)
        throw std::invalid_argument{ "The left bound of rng should be smaller than right bound."};

    //  generate random seeds
    std::random_device rd{};
    std::array<std::random_device::result_type, engine_type::state_size> seed_data{};
    std::ranges::generate(seed_data, std::ref(rd));

    //  create generator engine depends on seed sequence
    std::seed_seq seed_sequence(seed_data.begin(), seed_data.end());
    engine_type engine{seed_sequence};

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