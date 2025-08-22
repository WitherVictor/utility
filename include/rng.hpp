#pragma once

#include <concepts>
#include <random>
#include <algorithm>
#include <array>
#include <stdexcept>
#include <ranges>

template <typename EngineType = std::mt19937_64>
class base_rng {
protected:
    base_rng() {
        std::random_device rd{};
        std::array<std::random_device::result_type, EngineType::state_size> seed_data{};
        std::ranges::generate(seed_data, std::ref(rd));

        std::seed_seq seed_sequence(std::ranges::begin(seed_data), std::ranges::end(seed_data));
        m_engine = EngineType{seed_sequence};
    }
protected:
    EngineType m_engine;
};

template <typename T, typename EngineType = std::mt19937_64>
class rng;

template <std::integral T, typename EngineType>
class rng<T, EngineType> : public base_rng<EngineType> {
public:
    rng(T begin, T end)
        : base_rng<EngineType>(), m_range{begin, end}
    {
        if (begin > end)
            throw std::invalid_argument{"begin must be less than or equal to end"};
    }

    T operator()() { return m_range(base_rng<EngineType>::m_engine); }
private:
    std::uniform_int_distribution<T> m_range;
};

template <std::floating_point T, typename EngineType>
class rng<T, EngineType> : public base_rng<EngineType> {
public:
    rng(T begin, T end)
        : base_rng<EngineType>(), m_range{begin, end}
    {
        if (begin >= end)
            throw std::invalid_argument{"begin must be less than end"};
    }

    T operator()() { return m_range(base_rng<EngineType>::m_engine); }
private:
    std::uniform_real_distribution<T> m_range;
};

template <typename T, typename U>
rng(T, U) -> rng<std::common_type_t<T, U>>;