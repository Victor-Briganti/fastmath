#include "fastmath.h"

#include <cmath>

template <typename T> static T kernel_asin(T x) {
  static_assert(std::is_same_v<T, float> || std::is_same_v<T, double>,
                "Invalid type for this function");
  constexpr T pi2 = static_cast<T>(M_PI_2);
  constexpr T one = static_cast<T>(1.0);

  if (x >= one)
    return pi2;

  if (x <= -one)
    return -pi2;

  T frac;
  if constexpr (std::is_same_v<T, float>) {
    frac = sqrtf(one - x * x);
  } else if constexpr (std::is_same_v<T, double>) {
    frac = sqrt(one - x * x);
  }

  if (frac < static_cast<T>(1e-7))
    return (x < 0) ? -pi2 : pi2;

  if constexpr (std::is_same_v<T, float>) {
    return atanf(x / frac);
  } else if constexpr (std::is_same_v<T, double>) {
    return atan(x / frac);
  }
}

float fast_asinf(float x) { return kernel_asin<float>(x); }

double fast_asin(double x) { return kernel_asin<double>(x); }
