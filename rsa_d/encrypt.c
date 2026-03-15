#include "keygen.h"
#include <gmp.h>

void encrypt(mpz_t ciphertext, mpz_t message, struct PublicKey *pub) {
  mpz_powm(ciphertext, message, pub->e, pub->n);
}
