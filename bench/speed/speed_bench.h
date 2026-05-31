#pragma once

#include <chrono>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <string>
#include <type_traits>
#include <limits>

#include "../rand.h"
#include "fastmath.h"

template<typename T>
volatile T sink_var;

template <typename F> 
static double time_it(F &&func) {
  auto start = std::chrono::steady_clock::now();
  func();
  auto end = std::chrono::steady_clock::now();
  return std::chrono::duration<double>(end - start).count();
}

template <typename T, typename Func1, typename Func2>
void run_speed_bench_1arg(const char* name, Func1 common_fn, Func2 fast_fn, 
                          T lower = std::numeric_limits<T>::min(), 
                          T upper = std::numeric_limits<T>::max()) {
  constexpr size_t N = 100'000'000;
  constexpr int REPS = 10;

  std::vector<T> inputs = gen_random_real<T>(N, lower, upper);
  
  std::vector<double> fastSpeed;
  std::vector<double> commonSpeed;
  fastSpeed.reserve(REPS);
  commonSpeed.reserve(REPS);
  
  auto bench_fast = [&]() {
    T acc = 0;
    for (size_t i = 0; i < N; i++) {
      acc += fast_fn(inputs[i]);
    }
    sink_var<T> = acc;
  };
  
  auto bench_std = [&]() {
    T acc = 0;
    for (size_t i = 0; i < N; i++) {
      acc += common_fn(inputs[i]);
    }
    sink_var<T> = acc;
  };

  for (int i = 0; i < REPS; i++) {
    fastSpeed.push_back(time_it(bench_fast));
    commonSpeed.push_back(time_it(bench_std));
  }

  std::string suffix = std::is_same_v<T, float> ? "float" : "double";
  std::string filename = std::string("output/") + name + "_" + suffix + "_speed.csv";
  FILE *output = std::fopen(filename.c_str(), "w");
  if (!output) {
    std::perror("Failed to open output file");
    return;
  }
  
  fprintf(output, "common,fast\n");
  for (size_t i = 0; i < REPS; i++) {
    fprintf(output, "%.15g,%.15g\n", commonSpeed[i], fastSpeed[i]);
  }
  std::fclose(output);
}

template <typename T, typename Func1, typename Func2>
void run_speed_bench_2arg(const char* name, Func1 common_fn, Func2 fast_fn) {
  constexpr size_t N = 100'000'000;
  constexpr int REPS = 10;
  
  std::vector<T> inputA = gen_random_real<T>(N);
  std::vector<T> inputB = gen_random_real<T>(N);
  
  std::vector<double> fastSpeed;
  std::vector<double> commonSpeed;
  fastSpeed.reserve(REPS);
  commonSpeed.reserve(REPS);
  
  auto bench_fast = [&]() {
    T acc = 0;
    for (size_t i = 0; i < N; i++) {
      acc += fast_fn(inputA[i], inputB[i]);
    }
    sink_var<T> = acc;
  };
  
  auto bench_std = [&]() {
    T acc = 0;
    for (size_t i = 0; i < N; i++) {
      acc += common_fn(inputA[i], inputB[i]);
    }
    sink_var<T> = acc;
  };

  for (int i = 0; i < REPS; i++) {
    fastSpeed.push_back(time_it(bench_fast));
    commonSpeed.push_back(time_it(bench_std));
  }

  std::string suffix = std::is_same_v<T, float> ? "float" : "double";
  std::string filename = std::string("output/") + name + "_" + suffix + "_speed.csv";
  FILE *output = std::fopen(filename.c_str(), "w");
  if (!output) {
    std::perror("Failed to open output file");
    return;
  }
  
  fprintf(output, "common,fast\n");
  for (size_t i = 0; i < REPS; i++) {
    fprintf(output, "%.15g,%.15g\n", commonSpeed[i], fastSpeed[i]);
  }
  std::fclose(output);
}

#define RUN_SPEED_1ARG(NAME) \
    run_speed_bench_1arg<float>(#NAME, [](float x) { return std::NAME(x); }, [](float x) { return fast_##NAME##f(x); }); \
    run_speed_bench_1arg<double>(#NAME, [](double x) { return std::NAME(x); }, [](double x) { return fast_##NAME(x); });

#define RUN_SPEED_1ARG_LIM(NAME, LOWER, UPPER) \
    run_speed_bench_1arg<float>(#NAME, [](float x) { return std::NAME(x); }, [](float x) { return fast_##NAME##f(x); }, static_cast<float>(LOWER), static_cast<float>(UPPER)); \
    run_speed_bench_1arg<double>(#NAME, [](double x) { return std::NAME(x); }, [](double x) { return fast_##NAME(x); }, static_cast<double>(LOWER), static_cast<double>(UPPER));

#define RUN_SPEED_1ARG_LOWER(NAME, LOWER) \
    run_speed_bench_1arg<float>(#NAME, [](float x) { return std::NAME(x); }, [](float x) { return fast_##NAME##f(x); }, static_cast<float>(LOWER), std::numeric_limits<float>::max()); \
    run_speed_bench_1arg<double>(#NAME, [](double x) { return std::NAME(x); }, [](double x) { return fast_##NAME(x); }, static_cast<double>(LOWER), std::numeric_limits<double>::max());

#define RUN_SPEED_2ARG(NAME) \
    run_speed_bench_2arg<float>(#NAME, [](float a, float b) { return std::NAME(a, b); }, [](float a, float b) { return fast_##NAME##f(a, b); }); \
    run_speed_bench_2arg<double>(#NAME, [](double a, double b) { return std::NAME(a, b); }, [](double a, double b) { return fast_##NAME(a, b); });
