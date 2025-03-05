#pragma once

#include <concepts>
#include <type_traits>

#include "is_bool.hpp"
#include "abs.hpp"

template <typename T>
T gcd_impl(T first, T last) {
    while (last > 0) {
        first %= last;
        std::swap(first, last);
    }

    return first;
}

template <typename T, typename U>
requires std::integral<T> && std::integral<U> &&
         (!is_bool_v<T>) && (!is_bool_v<U>)
std::common_type_t<T, U> gcd(T first, U last) {
    using common_type = std::common_type_t<T, U>;

    auto common_first = abs<common_type>(first);
    auto common_last = abs<common_type>(last);

    return gcd_impl(common_first, common_last);
}