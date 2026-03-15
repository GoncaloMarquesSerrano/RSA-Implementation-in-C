long long modular_exponentiation(long long base, long long exp, long long mod) {
  long long result = 1;
  base = base % mod;

  while (exp > 0) {
    if (exp % 2 != 0) {
      result = (result * base) % mod;
    }

    exp = exp >> 1; // Equivalent to exp / 2
    base = (base * base) % mod;
  }

  return result;
}
