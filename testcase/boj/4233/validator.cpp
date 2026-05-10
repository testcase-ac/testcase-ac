#include "testlib.h"
#include <cmath>

using namespace std;

// Fast modular exponentiation: computes (a^e) mod m
long long modPow(long long a, long long e, long long m) {
    long long res = 1 % m;
    a %= m;
    while (e > 0) {
        if (e & 1) {
            __int128 tmp = (__int128)res * a % m;
            res = (long long)tmp;
        }
        __int128 tmp = (__int128)a * a % m;
        a = (long long)tmp;
        e >>= 1;
    }
    return res;
}

// Deterministic primality test for n <= 1e9 using trial division up to sqrt(n)
bool isPrime(long long n) {
    if (n <= 1) return false;
    if (n == 2 || n == 3) return true;
    if (n % 2 == 0) return false;
    for (long long d = 3; d * d <= n; d += 2) {
        if (n % d == 0) return false;
    }
    return true;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int caseCount = 0;

    while (true) {
        long long p = inf.readLong(0LL, 1000000000LL, "p");
        inf.readSpace();
        long long a = inf.readLong(0LL, 1000000000LL, "a");
        inf.readEoln();

        // Last line "0 0"
        if (p == 0 && a == 0) {
            break;
        }

        ++caseCount;
        ensuref(caseCount <= 100000, "Too many test cases: %d (max 100000)", caseCount);

        // Validate range constraints for a normal test case
        ensuref(2 < p && p <= 1000000000LL,
                "For test case %d: p must satisfy 2 < p <= 1e9, got p = %lld",
                caseCount, p);
        ensuref(1 < a && a < p,
                "For test case %d: a must satisfy 1 < a < p, got a = %lld, p = %lld",
                caseCount, a, p);

        // Problem statement implies:
        // "p is a base-a pseudoprime" only considered when p is composite and a^p ≡ a (mod p).
        // Also, input guarantees nothing about primality, but typical tasks assume:
        // - If p is prime, then a^p ≡ a (mod p) holds.
        // We must NOT assume this; instead we just validate the *given* global guarantee:
        // The problem does not state such a global guarantee, so we do NOT check it.
        //
        // However, we must ensure that any *implied* guarantees are satisfied.
        // Here there is one: the definition of "가짜소수 (pseudoprime)" itself is local
        // (depends only on p and a), and there is no statement like
        // "for the given input, p is never prime" or "answer always exists".
        // Therefore, there is no additional global property that must be enforced.
        //
        // We only enforce canonical numeric format via readLong, and range via ensuref.
        // No further simulation/global checks are required by the statement.
        //
        // Therefore, no extra computations/ensures are added here.
    }

    // After processing "0 0", ensure no extra data
    inf.readEof();
}
