#include "../math/modular.h"
#include "keygen.h"

long long decrypt(long long ciphertext, struct PrivateKey priv) {
  return modular_exponentiation(ciphertext, priv.d, priv.n);
}
