#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int cases = inf.readInt(1, 20, "N");
    inf.readEoln();

    for (int tc = 1; tc <= cases; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(1, 500000, "n");
        inf.readSpace();
        int m = inf.readInt(1, 100, "m");
        inf.readSpace();
        long long x = inf.readLong(0LL, 1000000000LL, "X");
        inf.readSpace();
        long long y = inf.readLong(0LL, 1000000000LL, "Y");
        inf.readSpace();
        long long z = inf.readLong(1LL, 1000000000LL, "Z");
        inf.readEoln();

        ensuref(m <= n, "case %d has m=%d greater than n=%d", tc, m, n);
        (void)x;
        (void)y;

        for (int i = 0; i < m; ++i) {
            inf.readLong(0LL, z - 1, "A_i");
            inf.readEoln();
        }
    }

    inf.readEof();
}
