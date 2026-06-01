#include "fastmath.h"

#include <catch2/catch_test_macros.hpp>

#include <cmath>

namespace {

template <typename T> constexpr int kSamples = 20000;

template <typename T>
void check_unary(const T lower, const T upper, const T abs_tolerance,
                 const T rel_tolerance, T (*std_fn)(T), T (*fast_fn)(T)) {
  for (int i = 0; i <= kSamples<T>; ++i) {
    const T ratio = static_cast<T>(i) / static_cast<T>(kSamples<T>);
    const T x = lower + ((upper - lower) * ratio);
    const T common = std_fn(x);
    const T fast = fast_fn(x);
    if (!std::isfinite(common) || !std::isfinite(fast)) {
      continue;
    }
    const T diff = std::fabs(common - fast);
    REQUIRE(diff <= abs_tolerance + (rel_tolerance * std::fabs(common)));
  }
}

template <typename T>
void check_binary(const T lower_a, const T upper_a, const T lower_b,
                  const T upper_b, const T abs_tolerance,
                  const T rel_tolerance, T (*std_fn)(T, T), T (*fast_fn)(T, T)) {
  for (int i = 0; i <= kSamples<T>; ++i) {
    const T ratio = static_cast<T>(i) / static_cast<T>(kSamples<T>);
    const T a = lower_a + ((upper_a - lower_a) * ratio);
    const T b = lower_b + ((upper_b - lower_b) * ratio);
    const T common = std_fn(a, b);
    const T fast = fast_fn(a, b);
    if (!std::isfinite(common) || !std::isfinite(fast)) {
      continue;
    }
    const T diff = std::fabs(common - fast);
    REQUIRE(diff <= abs_tolerance + (rel_tolerance * std::fabs(common)));
  }
}

} // namespace

TEST_CASE("trigonometric functions") {
  check_unary<float>(-1.0F, 1.0F, 1e-5F, 1e-5F, std::sinf, fast_sinf);
  check_unary<double>(-1.0, 1.0, 1e-5, 1e-5, std::sin, fast_sin);

  check_unary<float>(-1.0F, 1.0F, 1e-5F, 1e-5F, std::cosf, fast_cosf);
  check_unary<double>(-1.0, 1.0, 1e-5, 1e-5, std::cos, fast_cos);

  check_unary<float>(-1.0F, 1.0F, 1e-5F, 1e-5F, std::tanf, fast_tanf);
  check_unary<double>(-1.0, 1.0, 1e-5, 1e-5, std::tan, fast_tan);

  check_unary<float>(-1.0F, 1.0F, 1e-5F, 1e-5F, std::asinf, fast_asinf);
  check_unary<double>(-1.0, 1.0, 1e-5, 1e-5, std::asin, fast_asin);

  check_unary<float>(-1.0F, 1.0F, 1e-5F, 1e-5F, std::acosf, fast_acosf);
  check_unary<double>(-1.0, 1.0, 1e-5, 1e-5, std::acos, fast_acos);

  check_unary<float>(-1.0F, 1.0F, 1e-5F, 1e-5F, std::atanf, fast_atanf);
  check_unary<double>(-1.0, 1.0, 1e-5, 1e-5, std::atan, fast_atan);
}

TEST_CASE("hyperbolic functions") {
  check_unary<float>(-1.0F, 1.0F, 1e-5F, 1e-5F, std::sinhf, fast_sinhf);
  check_unary<double>(-1.0, 1.0, 1e-5, 1e-5, std::sinh, fast_sinh);

  check_unary<float>(-1.0F, 1.0F, 1e-5F, 1e-5F, std::coshf, fast_coshf);
  check_unary<double>(-1.0, 1.0, 1e-5, 1e-5, std::cosh, fast_cosh);

  check_unary<float>(-1.0F, 1.0F, 1e-5F, 1e-5F, std::tanhf, fast_tanhf);
  check_unary<double>(-1.0, 1.0, 1e-5, 1e-5, std::tanh, fast_tanh);
}

TEST_CASE("exponential and logarithmic functions") {
  check_unary<float>(-4.0F, 4.0F, 5e-5F, 5e-5F, std::expf, fast_expf);
  check_unary<double>(-4.0, 4.0, 5e-5, 5e-5, std::exp, fast_exp);

  check_unary<float>(-4.0F, 4.0F, 5e-5F, 5e-5F, std::exp2f, fast_exp2f);
  check_unary<double>(-4.0, 4.0, 5e-5, 5e-5, std::exp2, fast_exp2);

  check_unary<float>(0.001F, 100.0F, 5e-5F, 5e-5F, std::logf, fast_logf);
  check_unary<double>(0.001, 100.0, 5e-5, 5e-5, std::log, fast_log);

  check_unary<float>(0.001F, 100.0F, 5e-5F, 5e-5F, std::log2f, fast_log2f);
  check_unary<double>(0.001, 100.0, 5e-5, 5e-5, std::log2, fast_log2);

  check_unary<float>(0.001F, 100.0F, 5e-5F, 5e-5F, std::log10f, fast_log10f);
  check_unary<double>(0.001, 100.0, 5e-5, 5e-5, std::log10, fast_log10);
}

TEST_CASE("power and root functions") {
  check_binary<float>(0.001F, 100.0F, -2.0F, 2.0F, 1e-2F, 2e-1F, std::powf,
                      fast_powf);
  check_binary<double>(0.001, 100.0, -2.0, 2.0, 1e-2, 2e-1, std::pow,
                       fast_pow);

  check_unary<float>(0.001F, 100.0F, 1e-5F, 1e-5F, std::sqrtf, fast_sqrtf);
  check_unary<double>(0.001, 100.0, 1e-5, 1e-5, std::sqrt, fast_sqrt);
}
