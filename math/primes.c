#include <gmp.h>
#include <stdbool.h>

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
