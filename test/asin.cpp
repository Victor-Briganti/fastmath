#include "fastmath.h"

#include <cmath>
#include <iomanip>
#include <iostream>

int main() {
  std::cout << "Positive values\n";
  for (double x = 0.0; x <= 1.0; x += 0.1) {
    double ref = std::asin(x);
    double test = fast_asin(x);

    double abs_err = std::fabs(test - ref);
    double rel_err = abs_err / ref;

    std::cout << std::setprecision(10) << "x=" << x << " abs_err=" << abs_err
              << " rel_err=" << rel_err << std::endl;
    std::cout << "Common: " << ref << "\n";
    std::cout << "Fast: " << test << "\n";
  }

  std::cout << "\nNegative values\n";
  for (double x = 0.0; x >= -1.0; x -= 0.1) {
    double ref = std::asin(-x);
    double test = fast_asin(-x);

    double abs_err = std::fabs(test - ref);
    double rel_err = abs_err / ref;

    std::cout << std::setprecision(10) << "x=" << -x << " abs_err=" << abs_err
              << " rel_err=" << rel_err << std::endl;
    std::cout << "Common: " << ref << "\n";
    std::cout << "Fast: " << test << "\n";
  }
}
