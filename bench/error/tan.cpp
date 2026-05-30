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

void bench_tan() {
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
  bench_tan();

  FILE *output = std::fopen("output/tan_error.csv", "w");
  if (!output) {
    std::perror("Failed to open output file");
    return -1;
  }

  fprintf(output, "x,common,fast,abs_err,rel_err\n");
  for (auto stat : benchVec) {
    fprintf(output, "%.10g,%.15g,%.15g,%.15g,%.15g\n", stat.x, stat.common,
            stat.fast, stat.abs_err, stat.rel_err);
  }

  return 0;
}
