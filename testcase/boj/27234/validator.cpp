#include "testlib.h"

static bool isPrime(int value) {
    if (value < 2) {
        return false;
    }
    for (int divisor = 2; 1LL * divisor * divisor <= value; ++divisor) {
        if (value % divisor == 0) {
            return false;
        }
    }
    return true;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 150, "N");
    inf.readSpace();
    int p = inf.readInt(2, 1000000000, "P");
    inf.readEoln();

    ensuref(isPrime(p), "P must be prime, but got %d", p);

    inf.readEof();
    return 0;
}
