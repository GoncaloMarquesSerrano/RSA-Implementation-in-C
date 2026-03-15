#include <gmp.h>
#ifndef GENERATE_LARGE_PRIME_H
#define GENERATE_LARGE_PRIME_H

void generate_large_prime(mpz_t result, unsigned int bits,
                          gmp_randstate_t state);

#endif
