#include "speed_bench.h"

int main() {
  RUN_SPEED_1ARG_LIM(sinh, 0.00001, 1000);
  return EXIT_SUCCESS;
}
