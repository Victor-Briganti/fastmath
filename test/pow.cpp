#include "fastmath.h"

#include <cmath>
#include <cstdio>
#include <cstdlib>

template <typename T> constexpr T REL_TOLERANCE = T(1e-3);

template <typename T> bool test_pow(T &max_abs_err, T &max_rel_err) {
  max_abs_err = 0;
  max_rel_err = 0;

  constexpr int NA = 256;
  constexpr int NB = 256;

  for (int i = 0; i <= NA; i++) {
    // a in [0.5, 2]
    T ta = T(i) / T(NA);
    T a = std::exp(std::log(T(0.5)) + ta * std::log(T(4)));

    for (int j = 0; j <= NB; j++) {
      // b in [-10, 10]
      T b = -10 + 20 * (T(j) / T(NB));

      T fast, common;

      if constexpr (std::is_same_v<T, float>) {
        fast = fast_powf(a, b);
      } else {
        fast = fast_pow(a, b);
      }

      common = std::pow(a, b);

      T abs_err = std::fabs(common - fast);
      T rel_err = abs_err / std::fabs(common);

      if (rel_err > REL_TOLERANCE<T>) {
        fprintf(
            stderr,
            "    [FAIL] a=%.9g b=%.9g abs_err=%.9g rel_err=%.9g common=%.9g "
            "fast=%.9g\n",
            a, b, abs_err, rel_err, common, fast);
        return false;
      }

      max_abs_err = (max_abs_err < abs_err) ? abs_err : max_abs_err;
      max_rel_err = (max_rel_err < rel_err) ? rel_err : max_rel_err;
    }
  }
  return true;
}

int main() {
  fprintf(stderr, "[TEST] fast_exp\n");

  float max_abs_errf, max_rel_errf;
  if (!test_pow<float>(max_abs_errf, max_rel_errf))
    return EXIT_FAILURE;

  fprintf(stderr,
          "    [PASS] fast_exp<float> max_abs_errf=%.10g max_rel_errf=%.10g\n",
          max_abs_errf, max_rel_errf);

  double max_abs_errd, max_rel_errd;
  if (!test_pow<double>(max_abs_errd, max_rel_errd))
    return EXIT_FAILURE;

  fprintf(stderr,
          "    [PASS] fast_exp<double> max_abs_err=%.10g max_rel_err=%.10g\n",
          max_abs_errd, max_rel_errd);
  return EXIT_SUCCESS;
}
