#include "testlib.h"

bool isPrime(int n) {
    if (n < 2) return false;
    for (int d = 2; 1LL * d * d <= n; ++d) {
        if (n % d == 0) return false;
    }
    return true;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int m = inf.readInt(2, 100000, "m");
    inf.readSpace();
    int seed = inf.readInt(1, m - 1, "Seed");
    inf.readSpace();
    int x1 = inf.readInt(1, m - 1, "X_1");
    inf.readSpace();
    int x2 = inf.readInt(1, m - 1, "X_2");
    inf.readEoln();
    inf.readEof();

    ensuref(isPrime(m), "m must be prime: %d", m);
    ensuref(seed != x1 || x1 == x2,
            "no a, c can satisfy both LCG steps when Seed == X_1 and X_1 != X_2");
}
