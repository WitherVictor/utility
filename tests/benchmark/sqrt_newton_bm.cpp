#include <benchmark/benchmark.h>

#include <cmath>
#include <sqrt_newton.hpp>

void sqrt_newton_common(benchmark::State& state) {
    for (auto _ : state) {
        benchmark::DoNotOptimize(::sqrt_newton(state.range()));
    }
}

void sqrt_common(benchmark::State& state) {
    for (auto _ : state) {
        benchmark::DoNotOptimize(std::sqrt(state.range()));
    }
}

BENCHMARK(sqrt_common)
    ->Arg(2)
    ->Arg(3)
    ->Arg(5)
    ->Arg(7)
    ->Arg(16)
    ->Arg(32)
    ->Arg(64)
    ->Arg(128);
BENCHMARK(sqrt_newton_common)
    ->Arg(2)
    ->Arg(3)
    ->Arg(5)
    ->Arg(7)
    ->Arg(16)
    ->Arg(32)
    ->Arg(64)
    ->Arg(128);

BENCHMARK_MAIN();