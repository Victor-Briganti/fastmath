#include "speed_bench.h"

int main() {
  RUN_SPEED_1ARG_LIM(acos, -1.0, 1.0);
  return EXIT_SUCCESS;
}
