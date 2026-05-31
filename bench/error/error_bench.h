#pragma once

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <limits>
#include <string>
#include <type_traits>
#include <vector>

#include "../rand.h"
#include "fastmath.h"

template <typename T, typename Func1, typename Func2>
void run_error_bench_1arg(const char *name, Func1 common_fn, Func2 fast_fn,
                          T lower = std::numeric_limits<T>::min(),
                          T upper = std::numeric_limits<T>::max()) {
  constexpr int N = 1000;
  std::vector<T> inputs = gen_random_real<T>(N, lower, upper);

  std::string suffix = std::is_same_v<T, float> ? "float" : "double";
  std::string filename =
      std::string("output/") + name + "_" + suffix + "_error.csv";
  FILE *output = std::fopen(filename.c_str(), "w");
  if (!output) {
    std::perror("Failed to open output file");
    return;
  }

  fprintf(output, "x,common,fast,abs_err,rel_err\n");
  for (int i = 0; i < N; i++) {
    T x = inputs[i];
    T common = common_fn(x);
    T fast = fast_fn(x);
    T abs_err = std::fabs(common - fast);
    T rel_err = abs_err / std::fabs(common);
    if constexpr (std::is_same_v<T, float>) {
      fprintf(output, "%.7g,%.7g,%.7g,%.7g,%.7g\n", x, common, fast, abs_err,
              rel_err);
    } else {
      fprintf(output, "%.15g,%.15g,%.15g,%.15g,%.15g\n", x, common, fast,
              abs_err, rel_err);
    }
  }
  std::fclose(output);
}

template <typename T, typename Func1, typename Func2>
void run_error_bench_2arg(const char *name, Func1 common_fn, Func2 fast_fn) {
  constexpr int N = 1000;
  std::vector<T> inputA = gen_random_real<T>(N);
  std::vector<T> inputB = gen_random_real<T>(N);

  std::string suffix = std::is_same_v<T, float> ? "float" : "double";
  std::string filename =
      std::string("output/") + name + "_" + suffix + "_error.csv";
  FILE *output = std::fopen(filename.c_str(), "w");
  if (!output) {
    std::perror("Failed to open output file");
    return;
  }

  fprintf(output, "a,b,common,fast,abs_err,rel_err\n");
  for (int i = 0; i < N; i++) {
    T a = inputA[i];
    T b = inputB[i];
    T common = common_fn(a, b);
    T fast = fast_fn(a, b);
    T abs_err = std::fabs(common - fast);
    T rel_err = abs_err / std::fabs(common);
    if constexpr (std::is_same_v<T, float>) {
      fprintf(output, "%.7g,%.7g,%.7g,%.7g,%.7g,%.7g\n", a, b, common, fast,
              abs_err, rel_err);
    } else {
      fprintf(output, "%.15g,%.15g,%.15g,%.15g,%.15g,%.15g\n", a, b, common,
              fast, abs_err, rel_err);
    }
  }
  std::fclose(output);
}

#define RUN_BENCH_1ARG(NAME)                                                   \
  run_error_bench_1arg<float>(                                                 \
      #NAME, [](float x) { return std::NAME(x); },                             \
      [](float x) { return fast_##NAME##f(x); });                              \
  run_error_bench_1arg<double>(                                                \
      #NAME, [](double x) { return std::NAME(x); },                            \
      [](double x) { return fast_##NAME(x); });

#define RUN_BENCH_1ARG_LIM(NAME, LOWER, UPPER)                                 \
  run_error_bench_1arg<float>(                                                 \
      #NAME, [](float x) { return std::NAME(x); },                             \
      [](float x) { return fast_##NAME##f(x); }, static_cast<float>(LOWER),    \
      static_cast<float>(UPPER));                                              \
  run_error_bench_1arg<double>(                                                \
      #NAME, [](double x) { return std::NAME(x); },                            \
      [](double x) { return fast_##NAME(x); }, static_cast<double>(LOWER),     \
      static_cast<double>(UPPER));

#define RUN_BENCH_1ARG_LOWER(NAME, LOWER)                                      \
  run_error_bench_1arg<float>(                                                 \
      #NAME, [](float x) { return std::NAME(x); },                             \
      [](float x) { return fast_##NAME##f(x); }, static_cast<float>(LOWER),    \
      std::numeric_limits<float>::max());                                      \
  run_error_bench_1arg<double>(                                                \
      #NAME, [](double x) { return std::NAME(x); },                            \
      [](double x) { return fast_##NAME(x); }, static_cast<double>(LOWER),     \
      std::numeric_limits<double>::max());

#define RUN_BENCH_2ARG(NAME)                                                   \
  run_error_bench_2arg<float>(                                                 \
      #NAME, [](float a, float b) { return std::NAME(a, b); },                 \
      [](float a, float b) { return fast_##NAME##f(a, b); });                  \
  run_error_bench_2arg<double>(                                                \
      #NAME, [](double a, double b) { return std::NAME(a, b); },               \
      [](double a, double b) { return fast_##NAME(a, b); });
