#include "testlib.h"

bool isPrime(int x) {
    if (x < 2) {
        return false;
    }
    for (int d = 2; 1LL * d * d <= x; ++d) {
        if (x % d == 0) {
            return false;
        }
    }
    return true;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int m = inf.readInt(1, 5000, "M");
    inf.readSpace();
    int k = inf.readInt(1000000, 10000000, "K");
    inf.readEoln();

    ensuref(isPrime(k), "K must be prime, got %d", k);

    inf.readEof();
}
