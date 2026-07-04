#include "testlib.h"

bool isPrime(int n) {
    if (n < 2) {
        return false;
    }
    if (n % 2 == 0) {
        return n == 2;
    }
    for (int d = 3; 1LL * d * d <= n; d += 2) {
        if (n % d == 0) {
            return false;
        }
    }
    return true;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int p = inf.readInt(3, 1000000000, "p");
    inf.readSpace();
    int k = inf.readInt(1, p - 1, "k");
    inf.readSpace();
    int t = inf.readInt(1, p - 2, "t");
    inf.readEoln();

    ensuref(isPrime(p), "p must be prime, got %d", p);

    inf.readEof();
}
