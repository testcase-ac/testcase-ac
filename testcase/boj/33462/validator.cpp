#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 200000, "n");
    inf.readSpace();
    long long d = inf.readLong(1LL, 1000000000LL, "D");
    inf.readSpace();
    long long x = inf.readLong(1LL, 1000000000LL, "X");
    inf.readEoln();
    ensuref(x >= 2, "X must be at least 2 because n >= 1 and each x_i must satisfy 1 <= x_i < X");

    for (int i = 0; i < n; ++i) {
        if (i > 0) {
            inf.readSpace();
        }
        inf.readLong(1LL, x - 1, "x_i");
    }
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        if (i > 0) {
            inf.readSpace();
        }
        inf.readLong(1LL, 1000000000LL, "y_i");
    }
    inf.readEoln();

    inf.readEof();
}
