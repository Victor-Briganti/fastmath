#include "error_bench.h"

int main() {
  RUN_BENCH_1ARG_LIM(exp2, 0.00001, 1000);
  return EXIT_SUCCESS;
}
