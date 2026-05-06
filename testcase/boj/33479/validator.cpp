#include "testlib.h"

using namespace std;

// Miller-Rabin primality test for 32/64-bit numbers
// Deterministic for n < 3,317,444,400,000,000,000 (enough for p <= 1e9)
bool is_prime(long long n) {
    if (n < 2) return false;
    if (n == 2 || n == 3) return true;
    if (n % 2 == 0) return false;
    long long d = n - 1;
    int s = 0;
    while (d % 2 == 0) {
        d /= 2;
        ++s;
    }
    // Bases for deterministic test up to 1e9
    int bases[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
    for (int a : bases) {
        if (a >= n) break;
        long long x = 1, p = d;
        long long base = a, mod = n;
        // Compute x = base^p % mod
        while (p) {
            if (p & 1) x = (__int128)x * base % mod;
            base = (__int128)base * base % mod;
            p >>= 1;
        }
        if (x == 1 || x == n - 1) continue;
        bool ok = false;
        for (int r = 1; r < s; ++r) {
            x = (__int128)x * x % n;
            if (x == n - 1) { ok = true; break; }
        }
        if (!ok) return false;
    }
    return true;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read p and N
    long long p = inf.readLong(2LL, 1000000000LL, "p");
    inf.readSpace();
    long long N = inf.readLong(1LL, 1000000000000000000LL, "N");
    inf.readEoln();

    // Check p is prime
    ensuref(is_prime(p), "p (%lld) is not a prime number", p);

    inf.readEof();
}
