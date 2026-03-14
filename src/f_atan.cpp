#include "fastmath.h"

#include <cmath>

template <typename T> static T kernel_atan(T x) {
  constexpr T pi2 = static_cast<T>(M_PI_2);
  constexpr T one = static_cast<T>(1.0);
  constexpr T c1 = static_cast<T>(0.33288950512027);
  constexpr T c2 = static_cast<T>(-0.08467922817644);
  constexpr T c3 = static_cast<T>(0.03252232640125);
  constexpr T c4 = static_cast<T>(-0.00749305860992);

  bool negative = false;
  if (x < 0) {
    x = -x;
    negative = true;
  }

  bool invert = false;
  if (x > one) {
    x = one / x;
    invert = true;
  }

  const T x2 = x * x;
  T poly = one;
  poly += c1 * x2;
  const T x4 = x2 * x2;
  poly += c2 * x4;
  poly += c3 * (x4 * x2);
  poly += c4 * (x4 * x4);

  T result = x / poly;
  if (invert)
    result = pi2 - result;
  if (negative)
    result = -result;

  return result;
}

float fast_atanf(float x) { return kernel_atan<float>(x); }

double fast_atan(double x) { return kernel_atan<double>(x); }
