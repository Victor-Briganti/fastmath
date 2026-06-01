#include "speed_bench.h"

int main() {
  RUN_SPEED_1ARG_LIM(tanh, 0.00001, 1000);
  return EXIT_SUCCESS;
}
