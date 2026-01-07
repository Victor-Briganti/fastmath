#include "fastmath.h"

#include <cmath>

template <typename T> static T kernel_atan(T x) {
  constexpr T pi2 = static_cast<T>(M_PI_2);
  constexpr T one = static_cast<T>(1.0);
  constexpr T c1 = static_cast<T>(0.33288950512027);
  constexpr T c2 = static_cast<T>(-0.08467922817644);
  constexpr T c3 = static_cast<T>(0.03252232640125);
  constexpr T c4 = static_cast<T>(-0.00749305860992);

  T offset = 0.0;

  if (x > one) {
    offset = pi2;
    x = -one / x;
  } else if (x < -one) {
    offset = -pi2;
    x = -one / x;
  }

  T x2 = x * x;
  T poly = 1.0;
  poly += c1 * x2;
  T x4 = x2 * x2;
  poly += c2 * x4;
  poly += c3 * (x4 * x2);
  poly += c4 * (x4 * x4);

  return offset + (x / poly);
}

float fast_atanf(float x) { return kernel_atan<float>(x); }

double fast_atan(double x) { return kernel_atan<double>(x); }

long double fast_atanl(long double x) { return kernel_atan<long double>(x); }
