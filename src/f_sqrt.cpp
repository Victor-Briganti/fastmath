#include "fastmath.h"
#include <cmath>

#define COEFF_SIZE 6

template <typename T> static T kernel_sqrt(T x) {
  constexpr T coeffs[COEFF_SIZE] = {T(1.0000032),   T(0.49985756),
                                    T(-0.12345242), T(0.05545629),
                                    T(-0.0225715),  T(0.00492283)};
  int exp;
  T acc, xp;

  // transform mantissa from [0.5, 1) -> [0, 1)
  T mantissa;
  if constexpr (std::is_same_v<T, float>) {
    mantissa = frexpf(x, &exp) * 2 - 1;
  } else if constexpr (std::is_same_v<T, double>) {
    mantissa = frexp(x, &exp) * 2 - 1;
  } else {
    static_assert(false, "Invalid type for this function");
  }

  exp = exp - 1;

  acc = coeffs[0] + coeffs[1] * mantissa;
  xp = mantissa * mantissa;

  for (int i = 2; i < COEFF_SIZE; i++) {
    acc += coeffs[i] * xp;
    xp *= mantissa;
  }

  // An odd input exponent means an extra sqrt(2) in the output
  if (exp % 2 != 0)
    acc *= static_cast<T>(M_SQRT2);

  if constexpr (std::is_same_v<T, float>) {
    return acc * ldexpf(1, exp >> 2);
  } else if constexpr (std::is_same_v<T, double>) {
    return acc * ldexp(1, exp >> 2);
  } else {
    static_assert(false, "Invalid type for this function");
  }
}

float fast_sqrtf(float x) { return kernel_sqrt<float>(x); }

double fast_sqrt(double x) { return kernel_sqrt<double>(x); }
