#include "testlib.h"

bool isPrime(int x) {
    if (x < 2) {
        return false;
    }
    for (int d = 2; d * d <= x; ++d) {
        if (x % d == 0) {
            return false;
        }
    }
    return true;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(0, 300, "N");
    inf.readSpace();
    int m = inf.readInt(0, 300, "M");
    inf.readSpace();
    long long k = inf.readLong(1LL, 1000000000000LL, "K");
    inf.readSpace();
    int p = inf.readInt(3, 1000000, "P");
    inf.readEoln();
    inf.readEof();

    ensuref(isPrime(p), "P must be prime: %d", p);

    (void)n;
    (void)m;
    (void)k;
}
