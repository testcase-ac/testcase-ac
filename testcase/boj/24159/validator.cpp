#include "testlib.h"

bool isPrime(int x) {
    if (x < 2) return false;
    for (int d = 2; d * d <= x; ++d) {
        if (x % d == 0) return false;
    }
    return true;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int p = inf.readInt(2, 9999, "p");
    inf.readEoln();
    ensuref(isPrime(p), "p must be prime, got %d", p);

    inf.readInt(1, 10000, "n");
    inf.readEoln();
    inf.readEof();
}
