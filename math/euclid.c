#include <gmp.h>
/*
long long gcd(long long a, long long b) {
  while (b != 0) {
    long long aux = b;
    b = a % b;
    a = aux;
  }
  return a;
}

long long extended_euclid(long long a, long long b, long long *x,
                          long long *y) {
  if (b == 0) {
    *x = 1;
    *y = 0;
    return a;
  }

  long long x1, y1;

  long long result = extended_euclid(b, a % b, &x1, &y1);

  *x = y1;
  *y = x1 - (a / b) * y1;

  return result;
}

long long mmi(long long e, long long phi) {
  long long x, y;
  long long g = extended_euclid(e, phi, &x, &y);
  if (g != 1) {
    fprintf(stderr, "...");
    return -1;
  }
  return (x % phi + phi) % phi;
}*/

int modular_inverse(mpz_t result, mpz_t e, mpz_t phi) {
  if (mpz_invert(result, e, phi) == 0) {
    return -1;
  }

  return 0;
}
