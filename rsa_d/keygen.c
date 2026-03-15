#include "keygen.h"
#include "../math/euclid.h"
#include "../math/primes.h"
#include <gmp.h>

int keygen(unsigned int bits, struct PublicKey *pub, struct PrivateKey *priv,
           gmp_randstate_t state) {

  mpz_t p, q, n, phi, e, d, aux;

  mpz_inits(p, q, n, phi, e, d, aux, NULL);

  generate_large_prime(p, bits / 2, state);
  generate_large_prime(q, bits / 2, state);

  mpz_mul(n, p, q);

  mpz_sub_ui(p, p, 1);
  mpz_sub_ui(q, q, 1);
  mpz_mul(phi, p, q);

  mpz_set_ui(e, 65537); // Common choice for e
  mpz_gcd(aux, e, phi);

  if (mpz_cmp_ui(aux, 1) != 0) {
    mpz_clears(p, q, n, phi, e, d, aux, NULL);
    return -1;
  }

  if (modular_inverse(d, e, phi) != 0) {
    mpz_clears(p, q, n, phi, e, d, aux, NULL);
    return -1;
  }

  mpz_set(pub->e, e);
  mpz_set(pub->n, n);

  mpz_set(priv->d, d);
  mpz_set(priv->n, n);

  mpz_clears(p, q, n, phi, e, d, aux, NULL);

  return 0;
}
