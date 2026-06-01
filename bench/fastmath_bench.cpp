#include "fastmath.h"

#include <benchmark/benchmark.h>

#include <cmath>

namespace {

template <typename T> constexpr int kBatch = 2048;

template <typename T, T (*fn)(T)>
static void bench_unary_fast(benchmark::State &state) {
  T x = static_cast<T>(state.range(0));
  for (auto _ : state) {
    for (int i = 0; i < kBatch<T>; ++i) {
      x = fn(x);
      benchmark::DoNotOptimize(x);
    }
  }
}

template <typename T, T (*fn)(T)>
static void bench_unary_std(benchmark::State &state) {
  T x = static_cast<T>(state.range(0));
  for (auto _ : state) {
    for (int i = 0; i < kBatch<T>; ++i) {
      x = fn(x);
      benchmark::DoNotOptimize(x);
    }
  }
}

template <typename T, T (*fn)(T, T)>
static void bench_binary_fast(benchmark::State &state) {
  T a = static_cast<T>(state.range(0));
  T b = static_cast<T>(state.range(1));
  for (auto _ : state) {
    for (int i = 0; i < kBatch<T>; ++i) {
      a = fn(a, b);
      benchmark::DoNotOptimize(a);
    }
  }
}

template <typename T, T (*fn)(T, T)>
static void bench_binary_std(benchmark::State &state) {
  T a = static_cast<T>(state.range(0));
  T b = static_cast<T>(state.range(1));
  for (auto _ : state) {
    for (int i = 0; i < kBatch<T>; ++i) {
      a = fn(a, b);
      benchmark::DoNotOptimize(a);
    }
  }
}

} // namespace

#define BENCH_UNARY_ALL(NAME, SEED)                                            \
  BENCHMARK((bench_unary_std<float, std::NAME##f>))->Arg(SEED);                \
  BENCHMARK((bench_unary_fast<float, fast_##NAME##f>))->Arg(SEED);             \
  BENCHMARK((bench_unary_std<double, std::NAME>))->Arg(SEED);                  \
  BENCHMARK((bench_unary_fast<double, fast_##NAME>))->Arg(SEED)

#define BENCH_BINARY_ALL(NAME, SEEDA, SEEDB)                                   \
  BENCHMARK((bench_binary_std<float, std::NAME##f>))->Args({SEEDA, SEEDB});    \
  BENCHMARK((bench_binary_fast<float, fast_##NAME##f>))->Args({SEEDA, SEEDB}); \
  BENCHMARK((bench_binary_std<double, std::NAME>))->Args({SEEDA, SEEDB});      \
  BENCHMARK((bench_binary_fast<double, fast_##NAME>))->Args({SEEDA, SEEDB})

BENCH_UNARY_ALL(sin, 1);
BENCH_UNARY_ALL(cos, 1);
BENCH_UNARY_ALL(tan, 1);
BENCH_UNARY_ALL(asin, 0.5);
BENCH_UNARY_ALL(acos, 0.5);
BENCH_UNARY_ALL(atan, 1);
BENCH_UNARY_ALL(sinh, 1);
BENCH_UNARY_ALL(cosh, 1);
BENCH_UNARY_ALL(tanh, 1);
BENCH_UNARY_ALL(exp, 1);
BENCH_UNARY_ALL(exp2, 1);
BENCH_UNARY_ALL(log, 2);
BENCH_UNARY_ALL(log2, 2);
BENCH_UNARY_ALL(log10, 2);
BENCH_UNARY_ALL(sqrt, 2);
BENCH_BINARY_ALL(pow, 2, 1);

BENCHMARK_MAIN();
