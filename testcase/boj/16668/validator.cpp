#include "testlib.h"
#include <vector>
#include <cmath>

using namespace std;

// Fast modular multiplication for up to ~1e9^2 using __int128
static inline long long mul_mod(long long a, long long b, long long mod) {
    return (long long)((__int128)a * (__int128)b % (__int128)mod);
}

// Modular exponentiation
static long long mod_pow(long long a, long long e, long long mod) {
    long long r = 1 % mod;
    a %= mod;
    while (e > 0) {
        if (e & 1) r = mul_mod(r, a, mod);
        a = mul_mod(a, a, mod);
        e >>= 1;
    }
    return r;
}

// Deterministic Miller-Rabin for 32-bit integers (n <= 2e9)
static bool isPrime32(long long n) {
    if (n < 2) return false;
    // small primes
    for (long long p : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29}) {
        if (n == p) return true;
        if (n % p == 0) return n == p;
    }
    long long d = n - 1;
    int s = 0;
    while ((d & 1) == 0) {
        d >>= 1;
        ++s;
    }

    auto check = [&](long long a) -> bool {
        if (a % n == 0) return true;
        long long x = mod_pow(a, d, n);
        if (x == 1 || x == n - 1) return true;
        for (int i = 1; i < s; ++i) {
            x = mul_mod(x, x, n);
            if (x == n - 1) return true;
        }
        return false;
    };

    // For 32-bit ints, bases {2,7,61} are enough, but we can use a bit more.
    for (long long a : {2, 7, 61}) {
        if (!check(a)) return false;
    }
    return true;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 400, "t");
    inf.readSpace();
    long long p = inf.readLong(100000000LL, 1000000000LL, "p");
    inf.readEoln();

    // Check that p is prime, as required by the statement.
    ensuref(isPrime32(p), "p (%lld) must be a prime number", p);

    // Read n for each test case
    for (int i = 0; i < t; ++i) {
        setTestCase(i + 1);
        int n = inf.readInt(1, 400, "n");
        inf.readEoln();
        (void)n; // 'n' is not otherwise constrained beyond the range
    }

    inf.readEof();
}
