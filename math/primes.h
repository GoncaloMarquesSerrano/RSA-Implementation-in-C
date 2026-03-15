#include <gmp.h>
#include <stdbool.h>
#ifndef IS_PRIME_H
#define IS_PRIME_H

bool is_prime(long long n);

#endif

#ifndef GENERATE_LARGE_PRIME_H
#define GENERATE_LARGE_PRIME_H

void generate_large_prime(mpz_t result, unsigned int bits,
                          gmp_randstate_t state);

#endif
