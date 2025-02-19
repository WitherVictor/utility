#pragma once

#include <concepts>
#include <random>
#include <algorithm>

template <std::integral Tp>
class rng {
public:
    rng(Tp begin, Tp end)
        : m_range{begin, end}
    {
        std::random_device rd{};
        std::array<Tp, std::mt19937_64::state_size> seed_data{};
        std::ranges::generate(seed_data, std::ref(rd));
        std::seed_seq seed_sequence(std::begin(seed_data), std::end(seed_data));

        m_engine = std::mt19937_64{seed_sequence};
    }

    Tp yield() { return m_range(m_engine); }
    Tp operator()() { return yield(); }
private:
    std::mt19937_64 m_engine;
    std::uniform_int_distribution<Tp> m_range;
};

template <typename Tp, typename Up>
rng(Tp, Up) -> rng<std::common_type_t<Tp, Up>>;