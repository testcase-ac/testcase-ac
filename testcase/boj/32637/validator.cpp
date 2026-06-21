#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    long long x = inf.readLong(1LL, 10000000000000LL, "x");
    inf.readSpace();
    int n = inf.readInt(1, 100000, "n");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        inf.readLong(-x, x, "a_i");
        if (i == n) {
            inf.readEoln();
        } else {
            inf.readSpace();
        }
    }

    int m = inf.readInt(1, 100000, "m");
    inf.readEoln();

    for (int i = 1; i <= m; ++i) {
        inf.readLong(0LL, x, "y");
        inf.readEoln();
    }

    inf.readEof();
}
