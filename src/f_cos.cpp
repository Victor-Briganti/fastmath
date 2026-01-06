#include "fastmath.h"
#include <cmath>

float fast_cosf(float x) { return fast_sinf(x + static_cast<float>(M_PI_2)); }

double fast_cos(double x) { return fast_sin(x + M_PI_2); }

long double fast_cosl(long double x) {
  return fast_sinl(x + static_cast<long double>(M_PI_2));
}
