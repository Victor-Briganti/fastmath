#include "fastmath.h"

#include <cmath>

float fast_tanhf(float x) {
  // Values above 19 or below -19 are all equal to 1
  if (x < -19)
    return -1;

  if (x > 19)
    return 1;

  const float ex2 = fast_expf(x * 2);
  return (ex2 - 1) / (ex2 + 1);
}

double fast_tanh(double x) {
  if (x < -19)
    return -1;

  if (x > 19)
    return 1;

  const double ex2 = fast_exp(x * 2);
  return (ex2 - 1) / (ex2 + 1);
}

long double fast_tanhl(long double x) {
  if (x < -19)
    return -1;

  if (x > 19)
    return 1;

  const long double ex2 = fast_expl(x * 2);
  return (ex2 - 1) / (ex2 + 1);
}
