#include "keygen.h"
#ifndef ENCRYPT_H
#define ENCRYPT_H

void encrypt(mpz_t ciphertext, mpz_t message, struct PublicKey *pub);

#endif // !#ifndef ENCRYPT_H
