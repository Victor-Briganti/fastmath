#include "error_bench.h"

int main() {
  RUN_BENCH_1ARG_LIM(atan, -M_PI_2 + 1e-3, M_PI_2 - 1e-3);
  return EXIT_SUCCESS;
}
