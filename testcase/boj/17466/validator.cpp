#include "testlib.h"

using namespace std;

// Simple primality test up to 1e8 using trial division up to sqrt(n)
bool isPrime(int p) {
    if (p < 2) return false;
    if (p % 2 == 0) return p == 2;
    for (int d = 3; (long long)d * d <= p; d += 2) {
        if (p % d == 0) return false;
    }
    return true;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Single line: N and P
    long long N = inf.readLong(1LL, 100000000LL, "N");
    inf.readSpace();
    long long P = inf.readLong(2LL, 100000000LL, "P");
    inf.readEoln();

    // Check N < P
    ensuref(N < P, "Constraint violated: N (%lld) must be less than P (%lld)", N, P);

    // Check that P is prime (problem guarantees P is prime)
    ensuref(isPrime((int)P), "P (%lld) must be a prime number", P);

    inf.readEof();
}
