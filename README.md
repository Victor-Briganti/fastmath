# Fastmath

Fastmath is a reimplementation of a subset of the standard math.h library. Its primary goal is to provide faster execution by trading strict numerical accuracy for performance. As a result, some functions may produce approximate (and in some cases unsafe) results.

This library is intended to be used alongside the `-ffast-math` flag in GCC or Clang. Since `-ffast-math` already relaxes IEEE compliance and mathematical guarantees.

All functions are available in both float and double variants.

Implemented functions

Trigonometric:
`sin`, `cos`, `tan`, `asin`, `acos`, `atan`

Hyperbolic:
`sinh`, `cosh`, `tanh`

Exponential and logarithmic:
`exp`, `exp2`, `log`, `log2`, `log10`

Other:
`pow`, `sqrt`

# Acknowledgments

This work would not be possible without the contributions of Robert Bristow-Johnson, whose algorithms and polynomial coefficients form the basis of several implementations used in this library.

# Build and run

Configure and build:

```bash
cmake -S . -B build
cmake --build build
```

Run tests:

```bash
ctest --test-dir build --output-on-failure
```

Run benchmarks:

```bash
./build/fastmath_bench
```

