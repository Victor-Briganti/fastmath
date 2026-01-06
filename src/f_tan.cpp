#include "fastmath.h"
#include <cmath>

float fast_tanf(float x) { return fast_sinf(x) / fast_cosf(x); }

double fast_tan(double x) { return fast_sin(x) / fast_cos(x); }

long double fast_tanl(long double x) { return fast_sinl(x) / fast_cosl(x); }
