#include <stdbool.h>

bool is_prime(long long n) {

  if (n < 2) {
    return false;
  }

  if (n == 2) {
    return true;
  }

  if (n % 2 == 0) {
    return false;
  }

  for (long long i = 3; i * i <= n; i++) {
    if (n % i == 0) {
      return false;
    }
  }

  return true;
}
