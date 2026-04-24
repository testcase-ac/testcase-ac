#include "testlib.h"
#include <cstdint>
using namespace std;

// Compute gcd of two non-negative 64-bit integers
static long long gcdll(long long a, long long b) {
    while (b != 0) {
        long long r = a % b;
        a = b;
        b = r;
    }
    return a;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Limits: 1 <= n, m < 2^63
    const long long MAX_VAL = 9223372036854775807LL;  // 2^63 - 1

    // Read the counts of '1's for A and B
    long long n = inf.readLong(1LL, MAX_VAL, "n");
    inf.readSpace();
    long long m = inf.readLong(1LL, MAX_VAL, "m");
    inf.readEoln();

    // The GCD of the two numbers A="111...1" (n times) and B (m times)
    // is "111...1" of length gcd(n, m). The problem statement guarantees
    // that the answer has at most 10^7 digits.
    long long g = gcdll(n, m);
    ensuref(g <= 10000000LL,
            "gcd(n, m) = %lld exceeds maximum allowed digit count 10000000", g);

    inf.readEof();
    return 0;
}
