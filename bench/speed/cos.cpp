#include "fastmath.h"

#include <chrono>
#include <cmath>
#include <cstdio>
#include <vector>

constexpr size_t N = 100'000'000;
constexpr int REPS = 10;

static volatile double sink;
static std::vector<double> inputs;
static std::vector<double> fastSpeed;
static std::vector<double> commonSpeed;

static void init_inputs() {
  inputs.resize(N);
  for (size_t i = 0; i < N; i++) {
    inputs[i] = -1.0 + 2.0 * double(i) / double(N);
  }
}

static double bench_fast_cos() {
  double acc = 0.0;
  for (size_t i = 0; i < N; i++) {
    acc += fast_cos(inputs[i]);
  }
  sink = acc;
  return acc;
}

static double bench_std_cos() {
  double acc = 0.0;
  for (size_t i = 0; i < N; i++) {
    acc += std::cos(inputs[i]);
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
  FILE *output = std::fopen("output/cos_speed.csv", "w");
  if (!output) {
    std::perror("Failed to open output file");
    return -1;
  }

  init_inputs();
  for (int i = 0; i < REPS; i++) {
    fastSpeed.push_back(time_it(bench_fast_cos));
    commonSpeed.push_back(time_it(bench_std_cos));
  }

  fprintf(output, "common,fast\n");
  for (size_t i = 0; i < REPS; i++)
    fprintf(output, "%.15g,%.15g\n", fastSpeed[i], commonSpeed[i]);

  return 0;
}
