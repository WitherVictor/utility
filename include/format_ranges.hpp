#pragma once

#include <format>
#include <ranges>

template <std::ranges::input_range Range>
struct std::formatter<Range> {
    using ValueType = std::ranges::range_value_t<Range>;
    std::formatter<ValueType> element_formatter;

    constexpr auto parse(auto& ctx) {
        return element_formatter.parse(ctx);
    }

    auto format(const Range& range, auto& ctx) const {
        auto out = ctx.out();

        out = std::format_to(out, "[");

        bool first = true;
        for (const auto& elem : range) {
            if (first)
                first = false;
            else
                out = std::format_to(out, ", ");

            out = element_formatter.format(elem, ctx);
        }

        return std::format_to(out, "]");
    }
};