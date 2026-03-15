#include "keygen.h"
#include <gmp.h>

void decrypt(mpz_t message, mpz_t ciphertext, struct PrivateKey *priv) {
  mpz_powm(message, ciphertext, priv->d, priv->n);
}
