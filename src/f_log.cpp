#include "fastmath.h"
#include <cmath>

template <typename T> static T kernel_log2(T x) {
  constexpr double coeffs[] = {
      3.89729184e-05,  1.44211130e+00, -7.17371181e-01, 4.64553842e-01,
      -3.15227816e-01, 1.97374547e-01, -1.02013711e-01, 3.89226868e-02,
      -9.47682649e-03, 1.08818382e-03};

  int exp;
  T acc, xp;

  // transform mantissa from [0.5, 1) -> [0, 1)
  const T mantissa = std::frexp(x, &exp) * 2 - 1;
  exp = exp - 1;

  acc = coeffs[0] + coeffs[1] * mantissa;
  xp = mantissa * mantissa;

  for (int i = 2; i < sizeof(coeffs) / sizeof(double); i++) {
    acc += coeffs[i] * xp;
    xp *= mantissa;
  }

  return acc + static_cast<T>(exp);
}

float fast_log2f(float x) { return kernel_log2<float>(x); }

double fast_log2(double x) { return kernel_log2<double>(x); }

long double fast_log2l(long double x) { return kernel_log2<long double>(x); }

float fast_logf(float x) { return M_LN2 * kernel_log2<float>(x); }

double fast_log(double x) { return M_LN2 * kernel_log2<double>(x); }

long double fast_logl(long double x) {
  return M_LN2 * kernel_log2<long double>(x);
}

float fast_log10f(float x) { return M_LOG10_2 * kernel_log2<float>(x); }

double fast_log10(double x) { return M_LOG10_2 * kernel_log2<double>(x); }

long double fast_log10l(long double x) {
  return M_LOG10_2 * kernel_log2<long double>(x);
}
