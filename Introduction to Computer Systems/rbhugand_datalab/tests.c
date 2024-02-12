/* Testing Code */

#include <limits.h>
#include <math.h>

/* Routines used by floation point test code */

/* Convert from bit level representation to floating point number */
float u2f(unsigned u) {
  union {
    unsigned u;
    float f;
  } a;
  a.u = u;
  return a.f;
}

/* Convert from floating point number to bit-level representation */
unsigned f2u(float f) {
  union {
    unsigned u;
    float f;
  } a;
  a.f = f;
  return a.u;
}


int test_tmin(void) {
  return 0x80000000;
}
int test_bitAnd(int x, int y)
{
  return x&y;
}
int test_negate(int x) {
  return -x;
}
int test_isEqual(int x, int y)
{
  return x == y;
}
int test_addOK(int x, int y)
{
    long long lsum = (long long) x + y;
    return lsum == (int) lsum;
}
int test_signMag2TwosComp(int x) {
  int sign = x < 0;
  int mag = x & 0x7FFFFFFF;
  return sign ? -mag : mag;
}
int test_satAdd(int x, int y)
{
  if (x > 0 && y > 0 && x+y < 0)
    return (0x7FFFFFFF);
  if (x < 0 && y < 0 && x+y >= 0)
    return (0x80000000);
  return x + y;
}
int test_dividePower2(int x, int n)
{
    int p2n = 1<<n;
    return x/p2n;
}
int test_replaceByte(int x, int n, int c)
{
    switch(n) {
    case 0:
      x = (x & 0xFFFFFF00) | c;
      break;
    case 1:
      x = (x & 0xFFFF00FF) | (c << 8);
      break;
    case 2:
      x = (x & 0xFF00FFFF) | (c << 16);
      break;
    default:
      x = (x & 0x00FFFFFF) | (c << 24);
      break;
    }
    return x;
}
unsigned test_floatAbsVal(unsigned uf) {
  float f = u2f(uf);
  unsigned unf = f2u(-f);
  if (isnan(f))
    return uf;
  /* An unfortunate hack to get around a limitation of the BDD Checker */
  if ((int) uf < 0)
      return unf;
  else
      return uf;
}
int test_floatIsEqual(unsigned uf, unsigned ug) {
    float f = u2f(uf);
    float g = u2f(ug);
    return f == g;
}
unsigned test_floatPower2(int x) {
  float result = 1.0;
  float p2 = 2.0;
  int recip = (x < 0);
  /* treat tmin specially */
  if ((unsigned)x == 0x80000000) {
      return 0;
  }
  if (recip) {
    x = -x;
    p2 = 0.5;
  }
  while (x > 0) {
    if (x & 0x1)
      result = result * p2;
    p2 = p2 * p2;
    x >>= 1;
  }
  return f2u(result);
}
