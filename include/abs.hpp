#pragma once

/**
 * @tparam T 传入函数的值类型
 * @param value 要被修改的值
 * @brief 计算传入值的绝对值
 * @return |value|
 */
template <typename T>
T abs(T value) {
    return value < 0 ? -value : value;
}