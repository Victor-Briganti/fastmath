#include "fastmath.h"
#include <cmath>

#define COEFF_SIZE 10

template <typename T> static T kernel_sqrt(T x) {
  static_assert(std::is_same_v<T, float> || std::is_same_v<T, double>,
                "Invalid type for this function");
  constexpr T coeffs[COEFF_SIZE] = {T(1.00000000e+00),  T(4.99999815e-01),
                                    T(-1.24994769e-01), T(6.24357941e-02),
                                    T(-3.86363763e-02), T(2.56286488e-02),
                                    T(-1.60201623e-02), T(8.08000306e-03),
                                    T(-2.71359669e-03), T(4.34204965e-04)};
  int exp;
  T acc, xp;

  // transform mantissa from [0.5, 1) -> [0, 1)
  T mantissa;
  if constexpr (std::is_same_v<T, float>) {
    mantissa = frexpf(x, &exp) * 2 - 1;
  } else if constexpr (std::is_same_v<T, double>) {
    mantissa = frexp(x, &exp) * 2 - 1;
  }
  exp = exp - 1;

  acc = coeffs[0] + coeffs[1] * mantissa;
  xp = mantissa * mantissa;

  for (int i = 2; i < COEFF_SIZE; i++) {
    acc += coeffs[i] * xp;
    xp *= mantissa;
  }

  // An odd input exponent means an extra sqrt(2) in the output
  if (exp & 1)
    acc *= static_cast<T>(M_SQRT2);

  if constexpr (std::is_same_v<T, float>) {
    return acc * ldexpf(1, exp >> 1);
  } else if constexpr (std::is_same_v<T, double>) {
    return acc * ldexp(1, exp >> 1);
  }
}

float fast_sqrtf(float x) { return kernel_sqrt<float>(x); }

double fast_sqrt(double x) { return kernel_sqrt<double>(x); }
