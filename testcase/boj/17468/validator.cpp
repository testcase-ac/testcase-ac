#include "testlib.h"
#include <cmath>
#include <string>

using namespace std;

// Miller-Rabin primality test for 64-bit integers
// Deterministic for n < 2^64 using bases {2,3,5,7,11,13,17,19,23,29,31,37}
typedef unsigned long long ull;

ull modmul(ull a, ull b, ull mod) {
    // (a * b) % mod, avoiding overflow
    __uint128_t res = (__uint128_t)a * b;
    return (ull)(res % mod);
}

ull modpow(ull a, ull b, ull mod) {
    ull res = 1;
    a %= mod;
    while (b) {
        if (b & 1) res = modmul(res, a, mod);
        a = modmul(a, a, mod);
        b >>= 1;
    }
    return res;
}

bool is_prime(ull n) {
    if (n < 2) return false;
    if (n < 4) return true;
    if (n % 2 == 0) return false;
    ull d = n - 1;
    int s = 0;
    while ((d & 1) == 0) {
        d >>= 1;
        ++s;
    }
    // All bases for deterministic MR up to 2^64
    static const ull bases[] = {2,3,5,7,11,13,17,19,23,29,31,37};
    for (ull a : bases) {
        if (a >= n) break;
        ull x = modpow(a, d, n);
        if (x == 1 || x == n-1) continue;
        bool ok = false;
        for (int r = 1; r < s; ++r) {
            x = modmul(x, x, n);
            if (x == n-1) { ok = true; break; }
        }
        if (!ok) return false;
    }
    return true;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and P
    long long N = inf.readLong(1LL, 10000000000LL, "N");
    inf.readSpace();
    long long P = inf.readLong(1LL, 10000000000LL, "P");
    inf.readEoln();

    ensuref(N < P, "N (%lld) must be strictly less than P (%lld)", N, P);

    // Check that P is prime
    ensuref(is_prime((ull)P), "P (%lld) is not a prime", P);

    inf.readEof();
}
