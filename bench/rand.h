#ifndef RAND_H
#define RAND_H

#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstring>
#include <limits>
#include <random>
#include <type_traits>

template <typename T> bool is_equal(T a, T b, T rel_tol = 1e-12f) {
  static_assert((std::is_same_v<T, float> || std::is_same_v<T, double>) &&
                "Function only supports real numbers");

  T diff = std::abs(a - b);
  T max = std::max(std::abs(a), std::abs(b));
  return diff <= rel_tol * max;
}

template <typename T>
std::vector<T> gen_random_real(size_t length,
                               T lower = std::numeric_limits<T>::min(),
                               T upper = std::numeric_limits<T>::max()) {
  static_assert((std::is_same_v<T, float> || std::is_same_v<T, double>) &&
                "Function only supports real numbers");
  assert(!std::isinf(upper) && !std::isinf(lower) &&
         "Upper & Lower Limit should not be inf");
  assert(lower < upper &&
         "Lower limit cannot be greater or equal to upper limit");

  std::mt19937_64 gen(2345678);
  std::vector<T> numbers;
  numbers.reserve(length);

  if ((is_equal(lower, std::numeric_limits<T>::min()) &&
       is_equal(upper, std::numeric_limits<T>::max())) ||
      lower == 0) {
    uint64_t bits;
    T number;

    while (numbers.size() < length) {
      bits = gen();
      std::memcpy(&number, &bits, sizeof(number));

      if (std::isnan(number) || std::isinf(number) ||
          (lower == 0 && number < 0) || number > upper) {
        continue;
      }

      numbers.push_back(number);
    }
  } else {
    std::uniform_real_distribution<T> dist(lower, upper);

    while (numbers.size() < length)
      numbers.push_back(dist(gen));
  }

  return numbers;
}

#endif // RAND_H
