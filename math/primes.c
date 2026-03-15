#include <gmp.h>
#include <stdbool.h>

/*
bool is_prime(long long n) {

  if (n < 2) {
    return false;
  }

  if (n == 2) {
    return true;
  }

  if (n % 2 == 0) {
    return false;
  }

  for (long long i = 3; i * i <= n; i++) {
    if (n % i == 0) {
      return false;
    }
  }

  return true;
}*/

void generate_large_prime(mpz_t result, unsigned int bits,
                          gmp_randstate_t state) {

  while (1) {
    mpz_urandomb(result, state, bits);
    mpz_setbit(result,
               bits - 1);  // Ensure the number has the desired bit length
    mpz_setbit(result, 0); // Ensure the number is odd

    if (mpz_probab_prime_p(result, 25) >
        0) { // 25 rounds of testing for primality
      break;
    }
  }
}
