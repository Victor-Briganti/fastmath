#include "fastmath.h"

#include <chrono>
#include <cmath>
#include <cstdio>
#include <vector>

constexpr int NA = 8192;
constexpr int NB = 8192;
constexpr int REPS = 10;

static volatile double sink;
struct PowInput {
  double a;
  double b;
};

static std::vector<PowInput> inputs;

static std::vector<double> fastSpeed;
static std::vector<double> commonSpeed;

static void init_inputs() {
  inputs.clear();
  inputs.reserve((NA + 1) * (NB + 1));

  for (int i = 0; i <= NA; i++) {
    double ta = double(i) / double(NA);
    double a = std::exp(std::log(0.5) + ta * std::log(4.0));

    for (int j = 0; j <= NB; j++) {
      double b = -10.0 + 20.0 * (double(j) / double(NB));
      inputs.push_back({a, b});
    }
  }
}

static double bench_fast_pow() {
  double acc = 0.0;
  for (const auto &in : inputs) {
    acc += fast_pow(in.a, in.b);
  }
  sink = acc;
  return acc;
}

static double bench_std_pow() {
  double acc = 0.0;
  for (const auto &in : inputs) {
    acc += std::pow(in.a, in.b);
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
  FILE *output = std::fopen("output/pow_speed.csv", "w");
  if (!output) {
    std::perror("Failed to open output file");
    return -1;
  }

  init_inputs();
  for (int i = 0; i < REPS; i++) {
    fastSpeed.push_back(time_it(bench_fast_pow));
    commonSpeed.push_back(time_it(bench_std_pow));
  }

  fprintf(output, "common,fast\n");
  for (size_t i = 0; i < REPS; i++)
    fprintf(output, "%.15g,%.15g\n", fastSpeed[i], commonSpeed[i]);

  return 0;
}
