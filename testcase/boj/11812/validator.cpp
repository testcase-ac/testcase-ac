#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    long long n = inf.readLong(1LL, 1000000000000000LL, "N");
    inf.readSpace();
    int k = inf.readInt(1, 1000, "K");
    inf.readSpace();
    int q = inf.readInt(1, 100000, "Q");
    inf.readEoln();

    for (int i = 1; i <= q; ++i) {
        long long x = inf.readLong(1LL, n, "x");
        inf.readSpace();
        long long y = inf.readLong(1LL, n, "y");
        inf.readEoln();

        ensuref(x != y, "query %d has equal nodes: %lld", i, x);
    }

    inf.readEof();
}
