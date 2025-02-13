#pragma once

#include <chrono>
#include <concepts>

/**
 * @brief 计算经过时间长度的类
 * 
 * @tparam ClockType 
 * @return requires 
 */
template <typename ClockType = std::chrono::steady_clock>
requires requires () { ClockType::now(); }
class timer {
public:
    timer()
        : begin{std::chrono::steady_clock::now()} {}

    void start() { begin = std::move(ClockType::now()); }

    template <typename TargetDuration = std::chrono::nanoseconds>
    auto now() { 
        if constexpr (std::same_as<TargetDuration, std::chrono::nanoseconds>)
            return ClockType::now() - begin;
        else
            return std::chrono::duration_cast<TargetDuration>(ClockType::now() - begin);
    }
private:
    std::chrono::time_point<ClockType> begin;
};