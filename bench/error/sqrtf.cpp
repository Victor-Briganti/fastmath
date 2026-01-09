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

constexpr int N = 500;
std::vector<BenchStats> benchVec;

static void bench_sqrtf() {
  benchVec.reserve(N + 1);

  float x = 1e-6f;
  for (int i = 0; i <= N; i++) {
    BenchStats stats;
    stats.x = x;

    stats.common = std::sqrt(x);
    stats.fast = fast_sqrtf(x);

    stats.abs_err = std::fabs(stats.common - stats.fast);
    stats.rel_err = stats.abs_err / std::fabs(stats.common);

    benchVec.push_back(stats);

    x *= 1.1f;
  }
}

int main() {
  bench_sqrtf();

  FILE *output = std::fopen("output/sqrtf_error.csv", "w");
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
