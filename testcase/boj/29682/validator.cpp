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

    int a = inf.readInt(1, 2000000000, "a");
    inf.readSpace();
    int m = inf.readInt(2, 2000000000, "m");
    inf.readEoln();

    ensuref(a < m, "expected a < m, got a=%d, m=%d", a, m);
    ensuref(isPrime(m), "m must be prime, got %d", m);

    inf.readEof();
}
