#include "speed_bench.h"

int main() {
  RUN_SPEED_1ARG_LIM(log2, 0.00001, 1000);
  return EXIT_SUCCESS;
}
