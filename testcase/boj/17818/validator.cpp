#include "testlib.h"
#include <cstdint>
#include <vector>
using namespace std;
using ull = unsigned long long;
using u128 = unsigned __int128;

// Compute a * b mod m safely for 64-bit numbers
ull mod_mul(ull a, ull b, ull m) {
    return (u128)a * b % m;
}

// Compute a^e mod m
ull mod_pow(ull a, ull e, ull m) {
    ull res = 1 % m;
    a %= m;
    while (e) {
        if (e & 1) res = mod_mul(res, a, m);
        a = mod_mul(a, a, m);
        e >>= 1;
    }
    return res;
}

// Miller-Rabin primality test for 64-bit integers
bool is_prime(ull n) {
    if (n < 2) return false;
    // small primes to test divisibility
    for (ull p : {2ull, 3ull, 5ull, 7ull, 11ull, 13ull, 17ull, 19ull, 23ull, 29ull, 31ull, 37ull}) {
        if (n % p == 0) return n == p;
    }
    // write n-1 as d * 2^s
    ull d = n - 1;
    int s = 0;
    while ((d & 1) == 0) {
        d >>= 1;
        s++;
    }
    // Deterministic bases for testing 64-bit n
    for (ull a : {2ull, 325ull, 9375ull, 28178ull, 450775ull, 9780504ull, 1795265022ull}) {
        if (a % n == 0) continue;
        ull x = mod_pow(a, d, n);
        if (x == 1 || x == n - 1) continue;
        bool composite = true;
        for (int r = 1; r < s; r++) {
            x = mod_mul(x, x, n);
            if (x == n - 1) {
                composite = false;
                break;
            }
        }
        if (composite) return false;
    }
    return true;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read two primes A and B
    const ull MINP = 2;
    const ull MAXP = 100000000000000ULL; // 1e14

    ull A = inf.readLong(MINP, MAXP, "A");
    inf.readSpace();
    ull B = inf.readLong(MINP, MAXP, "B");
    inf.readEoln();

    // A and B must be distinct
    ensuref(A != B, "A and B must be distinct primes (got both %llu)", A);

    // Check primality
    ensuref(is_prime(A), "A is not prime: %llu", A);
    ensuref(is_prime(B), "B is not prime: %llu", B);

    // No further input
    inf.readEof();
    return 0;
}
