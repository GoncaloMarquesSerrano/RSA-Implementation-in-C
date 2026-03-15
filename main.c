#include "rsa_d/decrypt.h"
#include "rsa_d/encrypt.h"
#include "rsa_d/keygen.h"
#include <stdio.h>

int main() {
  struct PublicKey pub;
  struct PrivateKey priv;

  if (keygen(61, 53, &pub, &priv) != 0) {
    printf("keygen failed\n");
    return 1;
  }

  printf("Public Key:  e=%lld, n=%lld\n", pub.e, pub.n);
  printf("Private Key: d=%lld, n=%lld\n", priv.d, priv.n);

  long long m = 65;
  long long c = encrypt(m, pub);
  long long decrypted = decrypt(c, priv);

  printf("Original:  %lld\n", m);
  printf("Encrypted: %lld\n", c);
  printf("Decrypted: %lld\n", decrypted);

  return 0;
}
