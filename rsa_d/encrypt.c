#include "../math/modular.h"
#include "keygen.h"

long long encrypt(long long message, struct PublicKey pub) {
  return modular_exponentiation(message, pub.e, pub.n);
}
