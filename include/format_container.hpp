#pragma once

#include <format>
#include <vector>

template <typename T>
struct std::formatter<std::vector<T>> : std::formatter<T> {
    template <typename ContextType>
    auto format(const std::vector<T>& vec, ContextType& ctx) const {
        auto out = ctx.out();

        out = std::format_to(out, "[");
        for (std::size_t index{}; index < vec.size(); index++) {
            out = std::format_to(out, "{}", vec.at(index));

            if (index != vec.size() - 1) {
                out = std::format_to(out, ", ");
            }
        }
        return std::format_to(out, "]");
    }
};