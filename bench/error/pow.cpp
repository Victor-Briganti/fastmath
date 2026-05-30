#include <cmath>
#include <cstdio>
#include <vector>

#include "../rand.h"
#include "fastmath.h"

struct BenchStats {
  double a;
  double b;
  double common;
  double fast;
  double abs_err;
  double rel_err;
};

struct PowInput {
  double a;
  double b;
};

constexpr int N = 1000;
std::vector<BenchStats> benchVec;

static void bench_pow() {
  benchVec.reserve(N);

  std::vector<double> inputA = gen_random_real<double>(N);
  std::vector<double> inputB = gen_random_real<double>(N);
  std::vector<PowInput> inputs;
  inputs.reserve(N);

  for (size_t i = 0; i < N; i++) {
    inputs.push_back({inputA[i], inputB[i]});
  }

  for (int i = 0; i < N; i++) {
    BenchStats stats;
    stats.a = inputs[i].a;
    stats.b = inputs[i].b;
    stats.common = std::pow(stats.a, stats.b);
    stats.fast = fast_pow(stats.a, stats.b);
    stats.abs_err = std::fabs(stats.common - stats.fast);
    stats.rel_err = stats.abs_err / std::fabs(stats.common);
    benchVec.push_back(stats);
  }
}

int main() {
  bench_pow();

  FILE *output = std::fopen("output/pow_error.csv", "w");
  if (!output) {
    std::perror("Failed to open output file");
    return -1;
  }

  fprintf(output, "a,b,common,fast,abs_err,rel_err\n");
  for (const auto &stat : benchVec) {
    fprintf(output, "%.9g,%.9g,%.15g,%.15g,%.15g,%.15g\n", stat.a, stat.b,
            stat.common, stat.fast, stat.abs_err, stat.rel_err);
  }

  return 0;
}
