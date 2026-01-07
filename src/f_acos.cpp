#include "fastmath.h"

#include <cmath>

float fast_acosf(float x) { return static_cast<float>(M_PI_2) - fast_asinf(x); }

double fast_acos(double x) { return M_PI_2 - fast_asin(x); }

long double fast_acosl(long double x) {
  return static_cast<long double>(M_PI_2) - fast_asinl(x);
}
