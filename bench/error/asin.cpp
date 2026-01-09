#include "fastmath.h"

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <vector>

struct BenchStats {
  double x;
  double common;
  double fast;
  double abs_err;
  double rel_err;
};

constexpr int N = 100;
std::vector<BenchStats> benchVec;

void bench_asin() {
  benchVec.reserve(N * 2);
  for (int i = 0; i <= N; i++) {
    BenchStats stats;
    stats.x = static_cast<double>(-1 + 2 * i) / static_cast<double>(N);

    if (stats.x >= 1)
      break;

    stats.common = std::asin(stats.x);
    stats.fast = fast_asin(stats.x);
    stats.abs_err = std::fabs(stats.common - stats.fast);
    stats.rel_err = stats.abs_err / std::fabs(stats.common);
    benchVec.push_back(stats);
  }

  for (int i = 0; i <= N; i++) {
    BenchStats stats;
    stats.x = -(static_cast<double>(-1 + 2 * i) / static_cast<double>(N));

    if (stats.x <= -1)
      break;

    stats.common = std::asin(stats.x);
    stats.fast = fast_asin(stats.x);
    stats.abs_err = std::fabs(stats.common - stats.fast);
    stats.rel_err = stats.abs_err / std::fabs(stats.common);
    benchVec.push_back(stats);
  }
}

int main() {
  bench_asin();

  FILE *output = std::fopen("output/asin_error.csv", "w");
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
