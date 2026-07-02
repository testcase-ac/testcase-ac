#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 100, "T");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(1, 100000, "N");
        inf.readSpace();
        long long c = inf.readLong(1LL, 1000000000000000000LL, "C");
        inf.readEoln();

        for (int i = 1; i <= n; ++i) {
            long long l = inf.readLong(1LL, 10000000000000LL, "L_i");
            inf.readSpace();
            long long r = inf.readLong(1LL, 10000000000000LL, "R_i");
            inf.readEoln();

            ensuref(l < r, "interval %d has L_i >= R_i: %lld >= %lld", i, l, r);
        }
    }

    inf.readEof();
}
