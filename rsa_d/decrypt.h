#include "keygen.h"
#include <gmp.h>
#ifndef DECRYPT_H
#define DECRYPT_H

void decrypt(mpz_t message, mpz_t ciphertext, struct PrivateKey *priv);

#endif // !#ifndef DECRYPT_H
#define DECRYPT_H
