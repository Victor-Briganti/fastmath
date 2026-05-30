#include <cmath>
#include <cstdio>
#include <vector>

#include "../rand.h"
#include "fastmath.h"

struct BenchStats {
  double x;
  double common;
  double fast;
  double abs_err;
  double rel_err;
};

constexpr int N = 1000;
std::vector<BenchStats> benchVec;

void bench_sqrt() {
  std::vector<double> inputs = gen_random_real<double>(N, 0);
  benchVec.reserve(N);
  for (int i = 0; i < N; i++) {
    BenchStats stats;
    stats.x = inputs[i];
    stats.common = std::acos(stats.x);
    stats.fast = fast_acos(stats.x);
    stats.abs_err = std::fabs(stats.common - stats.fast);
    stats.rel_err = stats.abs_err / std::fabs(stats.common);
    benchVec.push_back(stats);
  }
}

int main() {
  bench_sqrt();

  FILE *output = std::fopen("output/sqrt_error.csv", "w");
  if (!output) {
    std::perror("Failed to open output file");
    return EXIT_FAILURE;
  }

  fprintf(output, "x,common,fast,abs_err,rel_err\n");
  for (const auto &stat : benchVec) {
    fprintf(output, "%.15g,%.15g,%.15g,%.15g,%.15g\n", stat.x, stat.common,
            stat.fast, stat.abs_err, stat.rel_err);
  }

  std::fclose(output);
  return EXIT_SUCCESS;
}
