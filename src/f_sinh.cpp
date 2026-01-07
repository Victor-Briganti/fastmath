#include "fastmath.h"

#include <cmath>

float fast_sinhf(float x) {
  const float ex = fast_expf(x);
  const float exn = fast_expf(-x);
  return (ex - exn) / 2;
}

double fast_sinh(double x) {
  const double ex = fast_exp(x);
  const double exn = fast_exp(-x);
  return (ex - exn) / 2;
}

long double fast_sinhl(long double x) {
  const long double ex = fast_expl(x);
  const long double exn = fast_expl(-x);
  return (ex - exn) / 2;
}
