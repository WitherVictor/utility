#pragma once

#include <concepts>
#include <random>
#include <algorithm>
#include <array>
#include <stdexcept>

template <typename T>
class rng;

template <std::integral T>
class rng<T> {
public:
    rng(T begin, T end)
        : m_range{begin, end}
    {
        if (begin > end)
            throw std::invalid_argument{"begin must be less than or equal to end"};

        std::random_device rd{};
        std::array<std::random_device::result_type, std::mt19937_64::state_size> seed_data{};
        std::ranges::generate(seed_data, std::ref(rd));
        std::seed_seq seed_sequence(std::ranges::begin(seed_data), std::ranges::end(seed_data));

        m_engine = std::mt19937_64{seed_sequence};
    }

    T operator()() { return m_range(m_engine); }
private:
    std::mt19937_64 m_engine;
    std::uniform_int_distribution<T> m_range;
};

template <std::floating_point T>
class rng<T> {
public:
    rng(T begin, T end)
        : m_range{begin, end}
    {
        if (begin > end)
            throw std::invalid_argument{"begin must be less than or equal to end"};

        std::random_device rd{};
        std::array<std::random_device::result_type, std::mt19937_64::state_size> seed_data{};
        std::ranges::generate(seed_data, std::ref(rd));
        std::seed_seq seed_sequence(std::ranges::begin(seed_data), std::ranges::end(seed_data));

        m_engine = std::mt19937_64{seed_sequence};
    }

    T operator()() { return m_range(m_engine); }
private:
    std::mt19937_64 m_engine;
    std::uniform_real_distribution<T> m_range;
};

template <typename T, typename Up>
rng(T, Up) -> rng<std::common_type_t<T, Up>>;