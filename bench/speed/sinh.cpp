#include <chrono>
#include <cmath>
#include <cstdio>
#include <vector>

#include "../rand.h"
#include "fastmath.h"

constexpr size_t N = 100'000'000;
constexpr int REPS = 10;

static volatile double sink;
static std::vector<double> inputs;
static std::vector<double> fastSpeed;
static std::vector<double> commonSpeed;

static void init_inputs() { inputs = gen_random_real<double>(N); }

static double bench_fast_sinh() {
  double acc = 0.0;
  for (size_t i = 0; i < N; i++) {
    acc += fast_sinh(inputs[i]);
  }
  sink = acc;
  return acc;
}

static double bench_std_sinh() {
  double acc = 0.0;
  for (size_t i = 0; i < N; i++) {
    acc += std::sinh(inputs[i]);
  }
  sink = acc;
  return acc;
}

template <typename F> static double time_it(F &&func) {
  auto start = std::chrono::steady_clock::now();
  func();
  auto end = std::chrono::steady_clock::now();
  return std::chrono::duration<double>(end - start).count();
}

int main() {
  FILE *output = std::fopen("output/sinh_speed.csv", "w");
  if (!output) {
    std::perror("Failed to open output file");
    return -1;
  }

  init_inputs();
  for (int i = 0; i < REPS; i++) {
    fastSpeed.push_back(time_it(bench_fast_sinh));
    commonSpeed.push_back(time_it(bench_std_sinh));
  }

  fprintf(output, "common,fast\n");
  for (size_t i = 0; i < REPS; i++)
    fprintf(output, "%.15g,%.15g\n", fastSpeed[i], commonSpeed[i]);

  return 0;
}
