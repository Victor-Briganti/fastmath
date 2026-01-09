#include "fastmath.h"

#include <cmath>
#include <cstdio>
#include <cstdlib>

template <typename T> constexpr T REL_TOLERANCE = T(1e-2);
constexpr int N = 1024;

template <typename T> bool test_sinh(T &max_abs_err, T &max_rel_err) {
  max_abs_err = -1;
  max_rel_err = -1;

  T x = static_cast<T>(0.00001);
  for (int i = 0; i <= N; i++) {
    x *= static_cast<T>(1.1);

    T fast;
    if constexpr (std::is_same_v<T, float>) {
      fast = fast_sinhf(x);
    } else if constexpr (std::is_same_v<T, double>) {
      fast = fast_sinh(x);
    } else {
      fprintf(stderr,
              "    [FAIL] %s:%d Type not currently supported in tests\n",
              __FILE__, __LINE__);
      return false;
    }

    T common = std::sinh(x);
    T abs_err = std::fabs(common - fast);
    T rel_err = std::fabs(common - fast) / std::fabs(common);

    if (rel_err > REL_TOLERANCE<T>) {
      fprintf(stderr,
              "    [FAIL] %s:%d i=%d x=%.15g abs_err=%.15g rel_err=%.15g "
              "common=%.15g "
              "fast=%.15g\n",
              __FILE__, __LINE__, i, x, abs_err, rel_err, common, fast);
      return false;
    }

    max_abs_err = (max_abs_err < abs_err) ? abs_err : max_abs_err;
    max_rel_err = (max_rel_err < rel_err) ? rel_err : max_rel_err;
  }

  x = static_cast<T>(-0.00001);
  for (int i = 0; i <= N; i++) {
    x *= static_cast<T>(1.1);

    T fast;
    if constexpr (std::is_same_v<T, float>) {
      fast = fast_sinhf(x);
    } else if constexpr (std::is_same_v<T, double>) {
      fast = fast_sinh(x);
    } else {
      fprintf(stderr, "    [FAIL] Type not currently supported in tests\n");
      return false;
    }

    T common = std::sinh(x);
    T abs_err = std::fabs(common - fast);
    T rel_err = std::fabs(common - fast) / std::fabs(common);

    if (rel_err > REL_TOLERANCE<T>) {
      fprintf(stderr,
              "    [FAIL] %s:%d i=%d x=%.15g abs_err=%.15g rel_err=%.15g "
              "common=%.15g "
              "fast=%.15g\n",
              __FILE__, __LINE__, i, x, abs_err, rel_err, common, fast);
      return false;
    }

    max_abs_err = (max_abs_err < abs_err) ? abs_err : max_abs_err;
  }

  return true;
}

int main() {
  fprintf(stderr, "[TEST] fast_sinh\n");

  float max_abs_errf, max_rel_errf;
  if (!test_sinh<float>(max_abs_errf, max_rel_errf))
    return EXIT_FAILURE;

  fprintf(stderr,
          "    [PASS] fast_sinh<float> max_abs_errf=%.10g max_rel_errf=%.10g\n",
          max_abs_errf, max_rel_errf);

  double max_abs_errd, max_rel_errd;
  if (!test_sinh<double>(max_abs_errd, max_rel_errd))
    return EXIT_FAILURE;

  fprintf(stderr,
          "    [PASS] fast_sinh<double> max_abs_err=%.10g max_rel_err=%.10g\n",
          max_abs_errd, max_rel_errd);
  return EXIT_SUCCESS;
}
