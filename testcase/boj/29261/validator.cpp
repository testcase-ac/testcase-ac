#include "testlib.h"
#include <vector>
using namespace std;

// Simple primality check for P < 3e6
bool isPrime(int x) {
    if (x < 2) return false;
    if (x == 2 || x == 3) return true;
    if (x % 2 == 0) return false;
    for (int i = 3; 1LL * i * i <= x; i += 2) {
        if (x % i == 0) return false;
    }
    return true;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Single integer P
    int P = inf.readInt(2, 3000000 - 1, "P");
    inf.readEoln();

    // Check that P is actually prime, as stated.
    ensuref(isPrime(P), "P must be a prime, but %d is not prime", P);

    inf.readEof();
}
