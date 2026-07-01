#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 200000, "N");
    inf.readSpace();
    int k = inf.readInt(1, n, "k");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        long long l = inf.readLong(-1000000000LL, 1000000000LL, "L_i");
        inf.readSpace();
        long long r = inf.readLong(-1000000000LL, 1000000000LL, "R_i");
        ensuref(l <= r, "interval %d has L_i > R_i: %lld > %lld", i, l, r);
        inf.readEoln();
    }

    inf.readEof();
}
