#include "fastmath.h"

#include <cmath>
#include <iomanip>
#include <iostream>

int main() {
  std::cout << "Positive values\n";
  for (double x = 1e-6; x <= 1e6; x *= 10.0) {
    double ref = std::sinh(x);
    double test = fast_sinh(x);

    double abs_err = std::fabs(test - ref);
    double rel_err = abs_err / ref;

    std::cout << std::setprecision(10) << "x=" << x << " abs_err=" << abs_err
              << " rel_err=" << rel_err << std::endl;
    std::cout << "Common: " << ref << "\n";
    std::cout << "Fast: " << test << "\n";
  }

  std::cout << "\nNegative values\n";
  for (double x = 1e-6; x <= 1e6; x *= 10.0) {
    double ref = std::sinh(-x);
    double test = fast_sinh(-x);

    double abs_err = std::fabs(test - ref);
    double rel_err = abs_err / ref;

    std::cout << std::setprecision(10) << "x=" << -x << " abs_err=" << abs_err
              << " rel_err=" << rel_err << std::endl;
    std::cout << "Common: " << ref << "\n";
    std::cout << "Fast: " << test << "\n";
  }
}
