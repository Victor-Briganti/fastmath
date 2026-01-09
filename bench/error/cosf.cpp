#include "fastmath.h"

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <vector>

struct BenchStats {
  float x;
  float common;
  float fast;
  float abs_err;
  float rel_err;
};

constexpr int N = 100;
std::vector<BenchStats> benchVec;

void bench_cosf() {
  benchVec.reserve(N * 2);
  for (int i = 0; i <= N; i++) {
    BenchStats stats;
    stats.x = static_cast<float>(-1 + 2 * i) / static_cast<float>(N);
    stats.common = std::cos(stats.x);
    stats.fast = fast_cosf(stats.x);
    stats.abs_err = std::fabs(stats.common - stats.fast);
    stats.rel_err = stats.abs_err / std::fabs(stats.common);
    benchVec.push_back(stats);
  }

  for (int i = 0; i <= N; i++) {
    BenchStats stats;
    stats.x = -(static_cast<float>(-1 + 2 * i) / static_cast<float>(N));
    stats.common = std::cos(stats.x);
    stats.fast = fast_cosf(stats.x);
    stats.abs_err = std::fabs(stats.common - stats.fast);
    stats.rel_err = stats.abs_err / std::fabs(stats.common);
    benchVec.push_back(stats);
  }
}

int main() {
  bench_cosf();

  FILE *output = std::fopen("output/cosf_error.csv", "w");
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
