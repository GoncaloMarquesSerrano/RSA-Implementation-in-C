#include "rsa_d/decrypt.h"
#include "rsa_d/encrypt.h"
#include "rsa_d/keygen.h"
#include <gmp.h>
#include <stdio.h>
#include <time.h>

int main() {
  gmp_randstate_t state;
  gmp_randinit_mt(state);
  gmp_randseed_ui(state, time(NULL)); // Seed for reproducibility

  struct PublicKey pub;
  struct PrivateKey priv;

  mpz_inits(pub.e, pub.n, priv.d, priv.n, NULL);

  if (keygen(2048, &pub, &priv, state) != 0) {
    printf("keygen failed\n");
    return 1;
  }

  gmp_printf("Public Key: e=%Zd, n=%Zd\n", pub.e, pub.n);
  gmp_printf("PrivateKey Key:  d=%Zd, n=%Zd\n", priv.d, priv.n);

  mpz_t message;
  mpz_init(message);
  mpz_set_str(message, "12345678901234567890", 10); // Example message

  mpz_t ciphertext;
  mpz_init(ciphertext);

  encrypt(ciphertext, message, &pub);

  mpz_t decrypted_message;
  mpz_init(decrypted_message);

  decrypt(decrypted_message, ciphertext, &priv);

  gmp_printf("Original:  %Zd\n", message);
  gmp_printf("Encrypted: %Zd\n", ciphertext);
  gmp_printf("Decrypted: %Zd\n", decrypted_message);

  mpz_clear(pub.e);
  mpz_clear(pub.n);
  mpz_clear(priv.d);
  mpz_clear(priv.n);
  mpz_clear(message);
  mpz_clear(ciphertext);
  mpz_clear(decrypted_message);

  return 0;
}
