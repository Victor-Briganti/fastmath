#include "fastmath.h"
#include <cmath>

#define COEFF_SIZE 14

template <typename T> static T kernel_cos_pi(T x) {
  constexpr T coeffs[COEFF_SIZE] = {
      T(9.99999992e-01),  T(-5.58095804e-16), T(-4.93480139e+00),
      T(1.36699826e-14),  T(4.05869825e+00),  T(-1.26448668e-13),
      T(-1.33517440e+00), T(4.71045125e-13),  T(2.35063254e-01),
      T(-8.27975054e-13), T(-2.53909919e-02), T(6.85880321e-13),
      T(1.60531764e-03),  T(-2.16178305e-13)};

  T acc, xp;
  T integer;
  if constexpr (std::is_same_v<T, float>) {
    integer = roundf(x / 2);
  } else if constexpr (std::is_same_v<T, double>) {
    integer = round(x / 2);
  } else {
    static_assert(false, "Invalid type for this function");
  }

  x -= 2 * integer;

  acc = coeffs[0] + coeffs[1] * x;
  xp = x * x;

  for (int i = 2; i < COEFF_SIZE; i++) {
    acc += coeffs[i] * xp;
    xp *= x;
  }

  return acc;
}

float fast_cosf(float x) {
  return kernel_cos_pi(static_cast<float>(M_1_PI) * x);
}

double fast_cos(double x) { return kernel_cos_pi<double>(M_1_PI * x); }
