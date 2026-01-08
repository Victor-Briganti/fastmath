#include "fastmath.h"

#include <cmath>
#include <cstdio>
#include <cstdlib>

constexpr int N = 1000000;

template <typename T> constexpr T ABS_TOLERANCE = T(1e-5);

template <typename T> bool test_cos(T &max_abs_err) {
  max_abs_err = -1;

  for (int i = 0; i <= N; i++) {
    T x = static_cast<T>(-1 + 2 * i) / static_cast<T>(N);

    T common = std::cos(x);
    T fast;
    if constexpr (std::is_same_v<T, float>) {
      fast = fast_cosf(x);
    } else if constexpr (std::is_same_v<T, double>) {
      fast = fast_cos(x);
    } else {
      fprintf(stderr,
              "    [FAIL] %s:%d Type not currently supported in tests\n",
              __FILE__, __LINE__);
      return false;
    }

    T abs_err = std::fabs(common - fast);

    if (abs_err > ABS_TOLERANCE<T>) {
      fprintf(stderr,
              "    [FAIL] %s:%d i=%d x=%.15g abs_err=%.15g common=%.15g "
              "fast=%.15g\n",
              __FILE__, __LINE__, i, x, abs_err, common, fast);
      return false;
    }

    max_abs_err = (max_abs_err < abs_err) ? abs_err : max_abs_err;
  }

  for (int i = 0; i <= N; i++) {
    T x = -static_cast<T>(-1 + 2 * i) / static_cast<T>(N);

    T common = std::cos(x);
    T fast;
    if constexpr (std::is_same_v<T, float>) {
      fast = fast_cosf(x);
    } else if constexpr (std::is_same_v<T, double>) {
      fast = fast_cos(x);
    } else {
      fprintf(stderr, "    [FAIL] Type not currently supported in tests\n");
      return false;
    }

    T abs_err = std::fabs(common - fast);

    if (abs_err > ABS_TOLERANCE<T>) {
      fprintf(stderr,
              "    [FAIL] %s:%d i=%d x=%.15g abs_err=%.15g common=%.15g "
              "fast=%.15g\n",
              __FILE__, __LINE__, i, x, abs_err, common, fast);
      return false;
    }

    max_abs_err = (max_abs_err < abs_err) ? abs_err : max_abs_err;
  }

  return true;
}

int main() {
  fprintf(stderr, "[TEST] fast_cos\n");

  float max_abs_errf;
  if (!test_cos<float>(max_abs_errf))
    return EXIT_FAILURE;

  fprintf(stderr, "    [PASS] fast_cos<float> max_abs_errf=%.10g\n",
          max_abs_errf);

  double max_abs_errd;
  if (!test_cos<double>(max_abs_errd))
    return EXIT_FAILURE;

  fprintf(stderr, "    [PASS] fast_cos<double> max_abs_err=%.10g\n",
          max_abs_errd);
  return EXIT_SUCCESS;
}
