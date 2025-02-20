#pragma once

#include <algorithm>
#include <optional>
#include <format>
#include <regex>

//  ranges formatter for std::vector<T>
#include "format_ranges.hpp"
#include "rng.hpp"

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
        return generator() + dice_data.modifier;
    });

    return std::format("{} : {}", dice_info, result);
}