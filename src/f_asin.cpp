#include "fastmath.h"

#include <cmath>

float fast_asinf(float x) {
  constexpr float one = 1.0f;
  return fast_atanf(x / fast_sqrtf(one - x * x));
}

double fast_asin(double x) {
  constexpr double one = 1.0;
  return fast_atan(x / fast_sqrt(one - x * x));
}

long double fast_asinl(long double x) {
  constexpr long double one = 1.0L;
  return fast_atanl(x / fast_sqrtl(one - x * x));
}
