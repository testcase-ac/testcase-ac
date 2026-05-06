#include "testlib.h"
#include <vector>
#include <cmath>

using namespace std;

// Simple primality test good enough for K up to 1e9+7
bool isPrime(long long x) {
    if (x < 2) return false;
    if (x % 2 == 0) return x == 2;
    for (long long d = 3; d * d <= x; d += 2) {
        if (x % d == 0) return false;
    }
    return true;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Single test case: "N K"
    long long N = inf.readLong(1LL, 1000000LL, "N");
    inf.readSpace();
    long long K = inf.readLong(1000000LL, 1000000007LL, "K");
    inf.readEoln();

    // Additional constraint: K is prime
    ensuref(isPrime(K), "K must be prime, but %lld is not prime", K);

    inf.readEof();
}
