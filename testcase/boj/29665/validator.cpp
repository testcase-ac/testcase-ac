#include "testlib.h"

bool isPrime(int x) {
    if (x < 2) {
        return false;
    }
    for (long long d = 2; d * d <= x; ++d) {
        if (x % d == 0) {
            return false;
        }
    }
    return true;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "n");
    inf.readSpace();
    int k = inf.readInt(1, n, "k");
    inf.readSpace();
    int m = inf.readInt(1, 1000000000, "m");
    inf.readEoln();

    ensuref(isPrime(m), "m must be prime: %d", m);

    inf.readEof();
}
