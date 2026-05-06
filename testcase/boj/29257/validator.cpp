#include "testlib.h"

using namespace std;

bool is_prime(long long p) {
    if (p < 2) return false;
    if (p == 2) return true;
    if (p % 2 == 0) return false;
    for (long long d = 3; d * d <= p && d <= 1000000; d += 2) {
        if (p % d == 0) return false;
    }
    return true;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    long long N = inf.readLong(1LL, 1000000000000000000LL, "N");
    inf.readSpace();

    // Read M
    int M = inf.readInt(3, 45, "M");
    inf.readSpace();

    // Read P
    int P = inf.readInt(2, 1000000000 - 1, "P");
    inf.readEoln();

    // Check P is prime
    ensuref(is_prime(P), "P (%d) is not a prime number", P);

    inf.readEof();
}
