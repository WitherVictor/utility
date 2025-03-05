#pragma once

#include <type_traits>

template <typename T>
struct is_bool : std::false_type {};

template <>
struct is_bool<bool> : std::true_type {};

template <typename T>
constexpr bool is_bool_v = is_bool<T>::value;