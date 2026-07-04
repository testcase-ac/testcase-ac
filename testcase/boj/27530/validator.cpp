#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    long long n = inf.readLong(1LL, 1000000000LL, "N");
    inf.readSpace();
    long long m = inf.readLong(1LL, 1000000000LL, "M");
    inf.readSpace();
    int k = inf.readInt(1, 200000, "K");
    inf.readSpace();
    int q = inf.readInt(1, 200000, "Q");
    inf.readEoln();

    for (int i = 1; i <= k; ++i) {
        inf.readLong(1LL, n, "y_i");
        inf.readSpace();
        inf.readLong(1LL, m, "x_i");
        inf.readEoln();
    }

    for (int j = 1; j <= q; ++j) {
        inf.readLong(1LL, n, "y_j");
        inf.readSpace();
        inf.readLong(1LL, m, "x_j");
        inf.readSpace();
        inf.readLong(1LL, 1000000000LL, "t_j");
        inf.readEoln();
    }

    inf.readEof();
}
