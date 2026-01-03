//
//    FILE: __functions.c
//
//    fast and approximate transcendental functions
//
//    copyright (c) 2004  Robert Bristow-Johnson
//
//    rbj@audioimagination.com
//

#include "minimax.h"

float __sqrt(register float x) {
  if (x > 5.877471754e-39) {
    register float accumulator, xPower;
    register long intPart;
    register union {
      float f;
      long i;
    } xBits;

    xBits.f = x;

    intPart = ((xBits.i) >> 23); /* get biased exponent */
    intPart -= 127;              /* unbias it */

    x = (float)(xBits.i & 0x007FFFFF); /* mask off exponent leaving
                                          0x800000*(mantissa - 1) */
    x *= 1.192092895507812e-07;        /* divide by 0x800000 */

    accumulator = 1.0 + 0.49959804148061 * x;
    xPower = x * x;
    accumulator += -0.12047308243453 * xPower;
    xPower *= x;
    accumulator += 0.04585425015501 * xPower;
    xPower *= x;
    accumulator += -0.01076564682800 * xPower;

    if (intPart & 0x00000001) {
      accumulator *= ROOT2; /* an odd input exponent means an extra sqrt(2) in
                               the output */
    }

    xBits.i = intPart >> 1; /* divide exponent by 2, lose LSB */
    xBits.i += 127;         /* rebias exponent */
    xBits.i <<= 23;         /* move biased exponent into exponent bits */

    return accumulator * xBits.f;
  } else {
    return 0.0;
  }
}

float __log2(register float x) {
  if (x > 5.877471754e-39) {
    register float accumulator, xPower;
    register long intPart;

    register union {
      float f;
      long i;
    } xBits;

    xBits.f = x;

    intPart = ((xBits.i) >> 23); /* get biased exponent */
    intPart -= 127;              /* unbias it */

    x = (float)(xBits.i & 0x007FFFFF); /* mask off exponent leaving
                                          0x800000*(mantissa - 1) */
    x *= 1.192092895507812e-07;        /* divide by 0x800000 */

    accumulator = 1.44254494359510 * x;
    xPower = x * x;
    accumulator += -0.71814525675041 * xPower;
    xPower *= x;
    accumulator += 0.45754919692582 * xPower;
    xPower *= x;
    accumulator += -0.27790534462866 * xPower;
    xPower *= x;
    accumulator += 0.12179791068782 * xPower;
    xPower *= x;
    accumulator += -0.02584144982967 * xPower;

    return accumulator + (float)intPart;
  } else {
    return -HUGE;
  }
}

float __exp2(register float x) {
  if (x >= -127.0) {
    register float accumulator, xPower;
    register union {
      float f;
      long i;
    } xBits;

    xBits.i = (long)(x + FLOAT_OFFSET) - LONG_OFFSET; /* integer part */
    x -= (float)(xBits.i);                            /* fractional part */

    accumulator = 1.0 + 0.69303212081966 * x;
    xPower = x * x;
    accumulator += 0.24137976293709 * xPower;
    xPower *= x;
    accumulator += 0.05203236900844 * xPower;
    xPower *= x;
    accumulator += 0.01355574723481 * xPower;

    xBits.i += 127; /* bias integer part */
    xBits.i <<= 23; /* move biased int part into exponent bits */

    return accumulator * xBits.f;
  } else {
    return 0.0;
  }
}

float __log(register float x) { return LN2 * __log2(x); }

float __exp(register float x) { return __exp2(ONE_OVER_LN2 * x); }

float __pow(float x, float y) {
#if STD_MATH_LIB
  return (float)pow((double)x, (double)y);
#else
  return __exp2(y * __log2(x));
#endif
}

float __sin_pi(register float x) {
  register float accumulator, xPower, xSquared;

  register long evenIntPart = ((long)(0.5 * x + 1024.5) - 1024) << 1;
  x -= (float)evenIntPart;

  xSquared = x * x;
  accumulator = 3.14159265358979 * x;
  xPower = xSquared * x;
  accumulator += -5.16731953364340 * xPower;
  xPower *= xSquared;
  accumulator += 2.54620566822659 * xPower;
  xPower *= xSquared;
  accumulator += -0.586027023087261 * xPower;
  xPower *= xSquared;
  accumulator += 0.06554823491427 * xPower;

  return accumulator;
}

float __cos_pi(register float x) {
  register float accumulator, xPower, xSquared;

  register long evenIntPart = ((long)(0.5 * x + 1024.5) - 1024) << 1;
  x -= (float)evenIntPart;

  xSquared = x * x;
  accumulator = 1.57079632679490 * x; /* series for sin(PI/2*x) */
  xPower = xSquared * x;
  accumulator += -0.64596406188166 * xPower;
  xPower *= xSquared;
  accumulator += 0.07969158490912 * xPower;
  xPower *= xSquared;
  accumulator += -0.00467687997706 * xPower;
  xPower *= xSquared;
  accumulator += 0.00015303015470 * xPower;

  return 1.0 -
         2.0 * accumulator * accumulator; /* cos(w) = 1 - 2*(sin(w/2))^2 */
}

float __sin(register float x) {
  x *= ONE_OVER_PI;
  return __sin_pi(x);
}

float __cos(register float x) {
  x *= ONE_OVER_PI;
  return __cos_pi(x);
}

float __tan(register float x) {
  x *= ONE_OVER_PI;
  return __sin_pi(x) / __cos_pi(x);
}

float __atan(register float x) {
  register float accumulator, xPower, xSquared, offset;

  offset = 0.0;

  if (x < -1.0) {
    offset = -PI_2;
    x = -1.0 / x;
  } else if (x > 1.0) {
    offset = PI_2;
    x = -1.0 / x;
  }
  xSquared = x * x;
  accumulator = 1.0;
  xPower = xSquared;
  accumulator += 0.33288950512027 * xPower;
  xPower *= xSquared;
  accumulator += -0.08467922817644 * xPower;
  xPower *= xSquared;
  accumulator += 0.03252232640125 * xPower;
  xPower *= xSquared;
  accumulator += -0.00749305860992 * xPower;

  return offset + x / accumulator;
}

float __asin(register float x) { return __atan(x / __sqrt(1.0 - x * x)); }

float __acos(register float x) { return __atan(__sqrt(1.0 - x * x) / x); }

float __arg(float Imag, float Real) {
  register float accumulator, xPower, xSquared, offset, x;

  if (Imag > 0.0) {
    if (Imag <= -Real) {
      offset = PI;
      x = Imag / Real;
    } else if (Imag > Real) {
      offset = PI_2;
      x = -Real / Imag;
    } else {
      offset = 0.0;
      x = Imag / Real;
    }
  } else {
    if (Imag >= Real) {
      offset = -PI;
      x = Imag / Real;
    } else if (Imag < -Real) {
      offset = -PI_2;
      x = -Real / Imag;
    } else {
      offset = 0.0;
      x = Imag / Real;
    }
  }

  xSquared = x * x;
  accumulator = 1.0;
  xPower = xSquared;
  accumulator += 0.33288950512027 * xPower;
  xPower *= xSquared;
  accumulator += -0.08467922817644 * xPower;
  xPower *= xSquared;
  accumulator += 0.03252232640125 * xPower;
  xPower *= xSquared;
  accumulator += -0.00749305860992 * xPower;

  return offset + x / accumulator;
}

float __poly(float *a, int order, float x) {
  register float accumulator = 0.0, xPower;
  register int n;

  accumulator = a[0];
  xPower = x;
  for (n = 1; n <= order; n++) {
    accumulator += a[n] * xPower;
    xPower *= x;
  }

  return accumulator;
}

float __map(float *f, float scaler, float x) {
  register long i;

  x *= scaler;

  i = (long)(x + FLOAT_OFFSET) - LONG_OFFSET; /* round down without floor() */

  return f[i] + (f[i + 1] - f[i]) *
                    (x - (float)i); /* linear interpolate between points */
}

float __discreteMap(float *f, float scaler, float x) {
  register long i;

  x *= scaler;

  i = (long)(x + (FLOAT_OFFSET + 0.5)) - LONG_OFFSET; /* round to nearest */

  return f[i];
}

unsigned long __random() {
  static unsigned long seed0 = 0x5B7A2775, seed1 = 0x80C7169F;

  seed0 += seed1;
  seed1 += seed0;

  return seed1;
}
