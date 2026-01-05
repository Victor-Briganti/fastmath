#include "fastmath.h"
#include <cmath>

template <typename T> static T kernel_sqrt(T x) {
  constexpr double coeffs[] = {1.0000032,  0.49985756, -0.12345242,
                               0.05545629, -0.0225715, 0.00492283};
  int exp;
  T acc, xp;

  // transform mantissa from [0.5, 1) -> [0, 1)
  const T mantissa = frexp(x, &exp) * 2 - 1;
  exp = exp - 1;

  acc = coeffs[0] + coeffs[1] * mantissa;
  xp = mantissa * mantissa;

  for (int i = 2; i < sizeof(coeffs) / sizeof(double); i++) {
    acc += coeffs[i] * xp;
    xp *= mantissa;
  }

  // An odd input exponent means an extra sqrt(2) in the output
  if (exp % 2 != 0)
    acc *= static_cast<T>(M_SQRT2);

  return static_cast<T>(acc * ldexp(1, exp / 2));
}

float fast_sqrtf(float x) { return kernel_sqrt<float>(x); }

double fast_sqrt(double x) { return kernel_sqrt<double>(x); }

long double fast_sqrtl(long double x) { return kernel_sqrt<long double>(x); }
