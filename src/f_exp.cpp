#include "fastmath.h"
#include <cmath>

#define COEFF_SIZE 10

template <typename T> static T kernel_exp2(T x) {
  static_assert(std::is_same_v<T, float> || std::is_same_v<T, double>,
                "Invalid type for this function");
  constexpr T coeffs[COEFF_SIZE] = {T(1.00000000e+00), T(6.93147181e-01),
                                    T(2.40226507e-01), T(5.55041104e-02),
                                    T(9.61811830e-03), T(1.33339455e-03),
                                    T(1.53949984e-04), T(1.53693670e-05),
                                    T(1.22575650e-06), T(1.44242433e-07)};

  T acc, xp;
  T integer;
  if constexpr (std::is_same_v<T, float>) {
    integer = floorf(x);
  } else if constexpr (std::is_same_v<T, double>) {
    integer = floor(x);
  }
  const T decimal = x - integer;

  acc = coeffs[0] + coeffs[1] * decimal;
  xp = decimal * decimal;

  for (int i = 2; i < COEFF_SIZE; i++) {
    acc += coeffs[i] * xp;
    xp *= decimal;
  }

  if constexpr (std::is_same_v<T, float>) {
    return ldexpf(acc, static_cast<int>(integer));
  } else if constexpr (std::is_same_v<T, double>) {
    return ldexp(acc, static_cast<int>(integer));
  }
}

float fast_exp2f(float x) { return kernel_exp2<float>(x); }

double fast_exp2(double x) { return kernel_exp2<double>(x); }

float fast_expf(float x) {
  return kernel_exp2<float>(static_cast<float>(M_ONE_LN2) * x);
}

double fast_exp(double x) { return kernel_exp2<double>(M_ONE_LN2 * x); }
