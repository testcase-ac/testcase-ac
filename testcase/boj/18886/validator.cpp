#include "testlib.h"

bool isPrime(int x) {
    if (x < 2) {
        return false;
    }
    if (x % 2 == 0) {
        return x == 2;
    }
    for (int d = 3; 1LL * d * d <= x; d += 2) {
        if (x % d == 0) {
            return false;
        }
    }
    return true;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 250000, "n");
    inf.readSpace();
    int m = inf.readInt(100000000, 1000000000, "m");
    inf.readEoln();

    ensuref(isPrime(m), "m must be prime: %d", m);

    inf.readEof();
    return 0;
}
