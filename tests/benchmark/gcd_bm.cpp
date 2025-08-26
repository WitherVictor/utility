#include <benchmark/benchmark.h>

#include <gcd.hpp>  //  ::gcd
#include <numeric>  //  std::gcd

void gcd_bm(benchmark::State& state) {
    for (auto _ : state) {
        benchmark::DoNotOptimize(::gcd(state.range(0), state.range(1)));
    }
}

void std_gcd_bm(benchmark::State& state) {
    for (auto _ : state) {
        benchmark::DoNotOptimize(std::gcd(state.range(0), state.range(1)));
    }
}

BENCHMARK(std_gcd_bm)
    ->Args({18, 24})
    ->Args({54, 72})
    ->Args({600, 125})
    ->Args({-12, -18})
    ->Args({24, -36})
    ->Args({-44, 28})
    ->Args({42, 0})
    ->Args({0, 72});
BENCHMARK(gcd_bm)
    ->Args({18, 24})
    ->Args({54, 72})
    ->Args({600, 125})
    ->Args({-12, -18})
    ->Args({24, -36})
    ->Args({-44, 28})
    ->Args({42, 0})
    ->Args({0, 72});