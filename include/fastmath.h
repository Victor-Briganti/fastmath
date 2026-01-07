#ifndef __FASTMATH_H__
#define __FASTMATH_H__

#define M_LOG10_2 0.3010299956639812
#define M_ONE_LN2 1.4426950408889634

float fast_sqrtf(float x);
double fast_sqrt(double x);
long double fast_sqrtl(long double x);

float fast_log2f(float x);
double fast_log2(double x);
long double fast_log2l(long double x);

float fast_logf(float x);
double fast_log(double x);
long double fast_logl(long double x);

float fast_log10f(float x);
double fast_log10(double x);
long double fast_log10l(long double x);

float fast_exp2f(float x);
double fast_exp2(double x);
long double fast_exp2l(long double x);

float fast_expf(float x);
double fast_exp(double x);
long double fast_expl(long double x);

float fast_sinf(float x);
double fast_sin(double x);
long double fast_sinl(long double x);

float fast_cosf(float x);
double fast_cos(double x);
long double fast_cosl(long double x);

float fast_tanf(float x);
double fast_tan(double x);
long double fast_tanl(long double x);

float fast_powf(float x, float y);
double fast_pow(double x, double y);
long double fast_powl(long double x, long double y);

float fast_atanf(float x);
double fast_atan(double x);
long double fast_atanl(long double x);

float fast_asinf(float x);
double fast_asin(double x);
long double fast_asinl(long double x);

#endif // __FASTMATH_H__
