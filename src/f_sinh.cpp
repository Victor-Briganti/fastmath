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
