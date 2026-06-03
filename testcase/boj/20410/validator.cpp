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

bool hasParameters(int m, int seed, int x1, int x2) {
    for (int a = 0; a < m; ++a) {
        for (int c = 0; c < m; ++c) {
            if ((a * seed + c) % m == x1 && (a * x1 + c) % m == x2) {
                return true;
            }
        }
    }
    return false;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int m = inf.readInt(2, 100, "m");
    inf.readSpace();
    int seed = inf.readInt(1, m - 1, "Seed");
    inf.readSpace();
    int x1 = inf.readInt(1, m - 1, "X_1");
    inf.readSpace();
    int x2 = inf.readInt(1, m - 1, "X_2");
    inf.readEoln();
    inf.readEof();

    ensuref(isPrime(m), "m must be prime: %d", m);
    ensuref(hasParameters(m, seed, x1, x2),
            "no a, c with 0 <= a, c < m generate X_1 and X_2");
}
