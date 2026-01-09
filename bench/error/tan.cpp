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

void bench_tan() {
  constexpr double X_MIN = -double(M_PI_2) + double(1e-3);
  constexpr double X_MAX = double(M_PI_2) - double(1e-3);

  benchVec.reserve(N);
  for (int i = 0; i <= N; i++) {
    BenchStats stats;
    stats.x = X_MIN + (X_MAX - X_MIN) * (double(i) / double(N));
    stats.common = std::tan(stats.x);
    stats.fast = fast_tan(stats.x);
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
