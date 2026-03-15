#include <gmp.h>

/*
#ifndef PUBLIC_KEY_H
#define PUBLIC_KEY_H

struct PublicKey {
  long long e;
  long long n;
};

#endif // PUBLIC_KEY_H

#ifndef PRIVATE_KEY_H
#define PRIVATE_KEY_H

struct PrivateKey {
  long long d;
  long long n;
};

#endif // PRIVATE_KEY_H

#ifndef KEYGEN_H
#define KEYGEN_H

int keygen(long long p, long long q, struct PublicKey *pub,
           struct PrivateKey *priv);

#endif // KEYGEN_H*/

#ifndef PUBLIC_KEY_H
#define PUBLIC_KEY_H

struct PublicKey {
  mpz_t e;
  mpz_t n;
};

#endif // PUBLIC_KEY_H

#ifndef PRIVATE_KEY_H
#define PRIVATE_KEY_H

struct PrivateKey {
  mpz_t d;
  mpz_t n;
};

#endif // PRIVATE_KEY_H

#ifndef KEYGEN_H
#define KEYGEN_H

int keygen(unsigned int bits, struct PublicKey *pub, struct PrivateKey *priv,
           gmp_randstate_t state);

#endif // KEYGEN_H
