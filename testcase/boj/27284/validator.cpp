#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "N");
    inf.readSpace();
    int m = inf.readInt(1, 10, "M");
    inf.readEoln();
    ensuref(m <= n, "M must be at most N: M=%d, N=%d", m, n);

    for (int i = 1; i <= n; ++i) {
        inf.readLong(1LL, 1000000000LL, "h_i");
        inf.readSpace();
        inf.readLong(1LL, 1000000000LL, "s_i");
        inf.readEoln();
    }

    inf.readEof();
}
