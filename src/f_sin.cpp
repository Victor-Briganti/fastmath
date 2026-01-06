#include "fastmath.h"
#include <cmath>

#define COEFF_SIZE 13

template <typename T> static T kernel_sin_pi(T x) {
  constexpr T coeffs[COEFF_SIZE] = {
      T(1.55431223e-15),  T(3.14159173e+00),  T(-2.77555756e-16),
      T(-5.16768502e+00), T(-4.13280521e-14), T(2.54992664e+00),
      T(2.19456397e-13),  T(-5.98397406e-01), T(-4.23771695e-13),
      T(8.06047826e-02),  T(3.75954085e-13),  T(-6.04102785e-03),
      T(-1.23925516e-13)};

  T acc, xp;
  T integer;
  if constexpr (std::is_same_v<T, float>) {
    integer = roundf(x / 2);
  } else if constexpr (std::is_same_v<T, double>) {
    integer = round(x / 2);
  } else {
    integer = roundl(x / 2);
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

float fast_sinf(float x) {
  return kernel_sin_pi(static_cast<float>(M_1_PI) * x);
}

double fast_sin(double x) { return kernel_sin_pi(M_1_PI * x); }

long double fast_sinl(long double x) {
  return kernel_sin_pi(static_cast<long double>(M_1_PI) * x);
}
