#pragma once

#include <algorithm>
#include <concepts>
#include <optional>
#include <random>
#include <format>
#include <type_traits>
#include <regex>

//  format for std::vector<T>
#include <format_ranges.hpp>

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
private:
    std::mt19937_64 m_engine;
    std::uniform_int_distribution<Tp> m_range;
};

template <typename Tp, typename Up>
rng(Tp, Up) -> rng<std::common_type_t<Tp, Up>>;

struct dice_data {
    std::size_t count{};
    std::size_t face{};
    std::int64_t modifier{};
};

std::optional<dice_data> parse_dice_info(std::string dice_info) {
    std::regex pattern{R"((\d+)d(\d+)([+-]\d+)?)"};
    std::smatch match{};

    if (!std::regex_match(dice_info, match, pattern)) {
        return std::nullopt;
    }

    std::istringstream stringstream{dice_info};

    dice_data result{};

    stringstream >> result.count;
    stringstream.get();
    stringstream >> result.face;
    stringstream.get();
    stringstream >> result.modifier;

    return result;
}

template <typename Tp = std::int64_t>
std::string roll_dice(const std::string& dice_info) {
    auto parse_result = parse_dice_info(dice_info);
    if (!parse_result) {
        return "Invalid dice info";
    }

    auto dice_data = parse_result.value();

    static rng generator{1, dice_data.face};

    std::vector<Tp> result(dice_data.count);
    std::generate_n(result.begin(), dice_data.count, [&dice_data]() {
        return generator.yield() + dice_data.modifier;
    });

    return std::format("{} : {}", dice_info, result);
}