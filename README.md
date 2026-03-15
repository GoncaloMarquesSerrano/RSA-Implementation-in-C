## RSA from Scratch
### Implemented in C · Phases 1 & 2 complete

A ground-up implementation of the RSA cryptosystem in C, built as a learning project.

---

## What this is

RSA is a public-key cryptosystem that lets you encrypt a message with a public key and decrypt it with a private key. The security rests on a simple asymmetry: multiplying two large primes together is trivial, but factoring the result back into those primes is computationally hard.

This implementation covers the full cycle:

```
keygen(p, q)  →  public key (e, n)  +  private key (d, n)
encrypt(m, pub)   →  ciphertext c  =  m^e mod n
decrypt(c, priv)  →  plaintext  m  =  c^d mod n
```

---

## Project structure

```
rsa/
├── main.c                  entry point
├── Makefile
│
├── math/
│   ├── euclid.c / .h       modular inverse (via GMP)
│   ├── modular.c / .h      modular exponentiation (via GMP)
│   └── primes.c / .h       large prime generation (Miller-Rabin)
│
└── rsa/
    ├── keygen.c / .h       key generation
    ├── encrypt.c / .h      encryption
    └── decrypt.c / .h      decryption
```


---

## The algorithms

### GCD — Euclidean algorithm
The foundation of everything. Used to verify that `e` and `φ(n)` are coprime.

```
gcd(a, b):
    while b != 0:
        b, a = a % b, b
    return a
```

### Modular inverse — Extended Euclidean algorithm
Finds `d` such that `(d × e) mod φ(n) = 1`. This is the private key exponent.

Uses the identity: for any `a` and `b`, there exist integers `x` and `y` such that `ax + by = gcd(a, b)`. When `gcd = 1`, `x` is the modular inverse.

### Modular exponentiation — Exponentiation by squaring
Computes `base^exp mod m` efficiently. Without this, RSA is unusable even with small numbers — `m^e` grows astronomically large.

```
mod_pow(base, exp, mod):
    result = 1
    while exp > 0:
        if exp is odd → result = result × base (mod m)
        exp >>= 1
        base = base² (mod m)
    return result
```

### Prime generation — Miller-Rabin
Generates large random primes for key generation. Trial division is too slow for 1024-bit numbers — instead, a candidate is generated randomly and tested probabilistically.

```
generate_prime(bits, state):
    repeat:
        n = random number with k bits
        set highest bit  → ensures exactly k bits
        set lowest bit   → ensures odd

        if Miller-Rabin(n, 25 rounds) > 0:
            return n
```

With 25 rounds, the probability of a false positive is below `4^(-25)`.

### Key generation
```
p, q  = two random primes of bits/2 each
n     = p × q
φ(n)  = (p−1)(q−1)
e     = 65537           (standard choice)
d     = e⁻¹ mod φ(n)   (modular inverse)

public key  → (e, n)
private key → (d, n)
```

`e = 65537` is the industry standard — it is prime, has a short bit representation, and makes encryption fast.

---

## Build & run

```bash
make          # compile everything
make run      # compile and run
make clean    # remove build artifacts
```

Requires [GMP](https://gmplib.org/):
```bash
# Arch / Manjaro
pacman -S gmp

# Ubuntu / Debian
apt install libgmp-dev
```

**Example output with 2048-bit keys:**
```
Public Key:  e=65537, n=<617 digit number>
Private Key: d=<617 digit number>, n=<617 digit number>
Original:    12345678901234567890
Encrypted:   <617 digit number>
Decrypted:   12345678901234567890
```

---

## Two phases

### Phase 1 — `long long` arithmetic
The full RSA algorithm implemented with 64-bit integers. Primes are chosen manually, keys are small, and no external libraries are used. The goal was to understand the algorithm before scaling it.

All the core algorithms were written from scratch:
- Euclidean algorithm and extended variant
- Exponentiation by squaring
- Trial division primality test

### Phase 2 — GMP, 2048-bit keys
The `long long` types are replaced with `mpz_t` from the GMP library, enabling arbitrary-precision arithmetic. Key generation now produces real 2048-bit RSA keys with randomly generated primes.

The architecture did not change between phases — only the `math/` layer was updated.

---

## Limitations

- No padding scheme (OAEP or PKCS#1) — raw RSA is not semantically secure
- Messages must be smaller than `n`
- Not hardened against timing attacks
- For learning purposes only — do not use to protect real data

---

## What I learned

- Modular arithmetic and why it makes RSA possible
- The extended Euclidean algorithm and Bézout's identity
- Why naive exponentiation is useless and how squaring fixes it
- Miller-Rabin probabilistic primality testing
- Arbitrary-precision arithmetic with GMP
- Memory management with `mpz_init` / `mpz_clear`
- Building and evolving a multi-file C project with a Makefile
- Using `gdb` to debug a segfault by reading a backtrace

---

*Built across two sessions as a learning exercise.
