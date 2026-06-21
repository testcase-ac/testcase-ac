#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    long long n = inf.readLong(1LL, 1000000000LL, "N");
    inf.readSpace();
    int q = inf.readInt(1, 300000, "Q");
    inf.readEoln();

    ensuref(n % 2 == 1, "N must be odd: %lld", n);
    long long maxBlackCells = n * n;

    for (int i = 1; i <= q; ++i) {
        inf.readLong(0LL, maxBlackCells, "Q_i");
        if (i < q) {
            inf.readSpace();
        } else {
            inf.readEoln();
        }
    }

    inf.readEof();
}
