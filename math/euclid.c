#include <gmp.h>

int modular_inverse(mpz_t result, mpz_t e, mpz_t phi) {
  if (mpz_invert(result, e, phi) == 0) {
    return -1;
  }

  return 0;
}
