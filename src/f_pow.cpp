#include "fastmath.h"
#include <cmath>

float fast_powf(float x, float y) {
  const float sign = (x < 0) ? -1.0f : 1.0f;
  return sign * fast_exp2f(y * fast_log2f(sign * x));
}

double fast_pow(double x, double y) {
  const double sign = (x < 0) ? -1.0 : 1.0;
  return sign * fast_exp2(y * fast_log2(sign * x));
}

long double fast_powl(long double x, long double y) {
  const long double sign = (x < 0) ? -1.0L : 1.0L;
  return sign * fast_exp2l(y * fast_log2l(sign * x));
}
