#include "keygen.h"
#include "../math/euclid.h"
#include "../math/primes.h"
#include <gmp.h>

/*
int keygen(long long p, long long q, struct PublicKey *pub,
           struct PrivateKey *priv) {

  if (is_prime(p) == 0 || is_prime(q) == 0) {
    return -1; // p and q must be prime
  }

  long long n = p * q;

  long long phi = (p - 1) * (q - 1);

  long long e = 3;

  while (e < phi) {
    if (gcd(e, phi) == 1) {
      break; // e must be coprime to phi
    }

    e += 2; // Increment e to find the next odd number
  }

  if (e >= phi) {
    return -1; // No valid e found
  }

  long long d = mmi(e, phi); // Calculate d using the modular inverse

  if (d == -1) {
    return -1; // No valid d found
  }

  pub->e = e;
  pub->n = n;
  priv->d = d;
  priv->n = n;

  return 0; // Success
}
*/

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
