#include "fastmath.h"

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <vector>

struct BenchStats {
  float a;
  float b;
  float common;
  float fast;
  float abs_err;
  float rel_err;
};

constexpr int NA = 256;
constexpr int NB = 256;

std::vector<BenchStats> benchVec;

static void bench_powf() {
  benchVec.reserve((NA + 1) * (NB + 1));

  for (int i = 0; i <= NA; i++) {
    // a in [0.5, 2]
    float ta = float(i) / float(NA);
    float a = std::exp(std::log(0.5f) + ta * std::log(4.0f));

    for (int j = 0; j <= NB; j++) {
      // b in [-10, 10]
      float b = -10.0f + 20.0f * (float(j) / float(NB));

      BenchStats stats;
      stats.a = a;
      stats.b = b;

      stats.common = std::pow(a, b);
      stats.fast = fast_powf(a, b);

      stats.abs_err = std::fabs(stats.common - stats.fast);
      stats.rel_err = stats.abs_err / std::fabs(stats.common);

      benchVec.push_back(stats);
    }
  }
}

int main() {
  bench_powf();

  FILE *output = std::fopen("output/powf_error.csv", "w");
  if (!output) {
    std::perror("Failed to open output file");
    return -1;
  }

  fprintf(output, "a,b,common,fast,abs_err,rel_err\n");
  for (const auto &stat : benchVec) {
    fprintf(output, "%.9g,%.9g,%.15g,%.15g,%.15g,%.15g\n", stat.a, stat.b,
            stat.common, stat.fast, stat.abs_err, stat.rel_err);
  }

  std::fclose(output);
  return 0;
}
