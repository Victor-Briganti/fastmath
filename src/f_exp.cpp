#include "fastmath.h"
#include <cmath>

#define M_ONE_LN2 1.4426950408889634

template <typename T> static T kernel_exp2(T x) {
  constexpr T coeffs[] = {1.00000000e+00, 6.93147181e-01, 2.40226507e-01,
                          5.55041104e-02, 9.61811830e-03, 1.33339455e-03,
                          1.53949984e-04, 1.53693670e-05, 1.22575650e-06,
                          1.44242433e-07};
  T acc, xp;
  const T integer = floor(x);
  const T decimal = x - integer;

  acc = coeffs[0] + coeffs[1] * decimal;
  xp = decimal * decimal;

  for (int i = 2; i < sizeof(coeffs) / sizeof(T); i++) {
    acc += coeffs[i] * xp;
    xp *= decimal;
  }

  if constexpr (std::is_same_v<T, float> || std::is_same_v<T, double>) {
    return ldexp(acc, static_cast<int>(integer));
  } else {
    return ldexpl(acc, static_cast<int>(integer));
  }
}

float fast_exp2f(float x) { return kernel_exp2<float>(x); }

double fast_exp2(double x) { return kernel_exp2<double>(x); }

long double fast_exp2l(long double x) { return kernel_exp2<long double>(x); }

float fast_expf(float x) { return kernel_exp2<float>(M_ONE_LN2 * x); }

double fast_exp(double x) { return kernel_exp2<double>(M_ONE_LN2 * x); }

long double fast_expl(long double x) {
  return kernel_exp2<long double>(M_ONE_LN2 * x);
}
