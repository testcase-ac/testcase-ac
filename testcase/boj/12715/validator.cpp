#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int caseCount = inf.readInt(1, 20, "N");
    inf.readEoln();

    for (int t = 1; t <= caseCount; ++t) {
        setTestCase(t);

        int n = inf.readInt(1, 1000, "n");
        inf.readSpace();
        int m = inf.readInt(1, 100, "m");
        inf.readSpace();
        inf.readLong(0LL, 1000000000LL, "X");
        inf.readSpace();
        inf.readLong(0LL, 1000000000LL, "Y");
        inf.readSpace();
        long long z = inf.readLong(1LL, 1000000000LL, "Z");
        inf.readEoln();

        ensuref(m <= n, "case %d has m > n: m=%d, n=%d", t, m, n);

        for (int i = 0; i < m; ++i) {
            inf.readLong(0LL, z - 1, "A_i");
            inf.readEoln();
        }
    }

    inf.readEof();
    return 0;
}
