#include "keygen.h"
#include "../math/euclid.h"
#include "../math/primes.h"

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
