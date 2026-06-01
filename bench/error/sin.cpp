#include "error_bench.h"

int main() {
  RUN_BENCH_1ARG_LIM(sin, -1.0, 1.0);
  return EXIT_SUCCESS;
}
