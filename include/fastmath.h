#ifndef __FASTMATH_H__
#define __FASTMATH_H__

#define M_LOG10_2 0.3010299956639812
#define M_ONE_LN2 1.4426950408889634

//===----------------------------------------------------------------------===//
// Exponential Functions
//===----------------------------------------------------------------------===//

float fast_log2f(float x);
double fast_log2(double x);

float fast_logf(float x);
double fast_log(double x);

float fast_log10f(float x);
double fast_log10(double x);

float fast_exp2f(float x);
double fast_exp2(double x);

float fast_expf(float x);
double fast_exp(double x);

float fast_powf(float x, float y);
double fast_pow(double x, double y);

//===----------------------------------------------------------------------===//
// Trigonometric Functions
//===----------------------------------------------------------------------===//

float fast_sinf(float x);
double fast_sin(double x);

float fast_cosf(float x);
double fast_cos(double x);

float fast_tanf(float x);
double fast_tan(double x);

float fast_asinf(float x);
double fast_asin(double x);

float fast_acosf(float x);
double fast_acos(double x);

float fast_atanf(float x);
double fast_atan(double x);

//===----------------------------------------------------------------------===//
// Hyperbolic Functions
//===----------------------------------------------------------------------===//

float fast_sinhf(float x);
double fast_sinh(double x);

float fast_coshf(float x);
double fast_cosh(double x);

float fast_tanhf(float x);
double fast_tanh(double x);

//===----------------------------------------------------------------------===//
// Other Functions
//===----------------------------------------------------------------------===//

float fast_sqrtf(float x);
double fast_sqrt(double x);

#endif // __FASTMATH_H__
