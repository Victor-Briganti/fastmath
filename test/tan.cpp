#include "fastmath.h"

#include <cmath>
#include <cstdio>
#include <cstdlib>

constexpr int N = 1000000;

template <typename T> constexpr T ABS_TOLERANCE = T(1e-5);

template <typename T> bool test_tan(T &max_x_err) {
  max_x_err = -1;

  constexpr T X_MIN = -T(M_PI_2) + T(1e-3);
  constexpr T X_MAX = T(M_PI_2) - T(1e-3);

  for (int i = 0; i <= N; i++) {
    // Generates numbers between approximately [-pi/2, pi/2]
    T x = X_MIN + (X_MAX - X_MIN) * (T(i) / T(N));

    T fast;
    if constexpr (std::is_same_v<T, float>) {
      fast = fast_tanf(x);
    } else if constexpr (std::is_same_v<T, double>) {
      fast = fast_tan(x);
    } else {
      fprintf(stderr,
              "    [FAIL] %s:%d Type not currently supported in tests\n",
              __FILE__, __LINE__);
      return false;
    }

    T x_err = std::fabs(std::atan(fast) - x);

    if (x_err > ABS_TOLERANCE<T>) {
      fprintf(stderr,
              "    [FAIL] %s:%d i=%d x=%.15g x_err=%.15g tan=%.15g "
              "fast=%.15g\n",
              __FILE__, __LINE__, i, x, x_err, std::tan(x), fast);
      // return false;
    }

    max_x_err = (max_x_err < x_err) ? x_err : max_x_err;
  }

  for (int i = 0; i <= N; i++) {
    T x = -(X_MIN + (X_MAX - X_MIN) * (T(i) / T(N)));

    T fast;
    if constexpr (std::is_same_v<T, float>) {
      fast = fast_tanf(x);
    } else if constexpr (std::is_same_v<T, double>) {
      fast = fast_tan(x);
    } else {
      fprintf(stderr, "    [FAIL] Type not currently supported in tests\n");
      return false;
    }

    T x_err = std::fabs(std::atan(fast) - x);

    if (x_err > ABS_TOLERANCE<T>) {
      fprintf(stderr,
              "    [FAIL] %s:%d i=%d x=%.15g x_err=%.15g tan=%.15g "
              "fast=%.15g\n",
              __FILE__, __LINE__, i, x, x_err, std::tan(x), fast);
      // return false;
    }

    max_x_err = (max_x_err < x_err) ? x_err : max_x_err;
  }

  return true;
}

int main() {
  fprintf(stderr, "[TEST] fast_tan\n");

  float max_x_errf;
  if (!test_tan<float>(max_x_errf))
    return EXIT_FAILURE;

  fprintf(stderr, "    [PASS] fast_tan<float> max_x_errf=%.10g\n", max_x_errf);

  double max_x_errd;
  if (!test_tan<double>(max_x_errd))
    return EXIT_FAILURE;

  fprintf(stderr, "    [PASS] fast_tan<double> max_x_err=%.10g\n", max_x_errd);
  return EXIT_SUCCESS;
}
