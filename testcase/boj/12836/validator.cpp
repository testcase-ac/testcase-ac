#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: The statement only writes N <= 10^4, but N represents lived days and
    // query positions are defined on days 1..N, so an empty day range is rejected.
    int n = inf.readInt(1, 10000, "N");
    inf.readSpace();
    int q = inf.readInt(0, 1000, "Q");
    inf.readEoln();

    for (int i = 1; i <= q; ++i) {
        int type = inf.readInt(1, 2, "query_type");
        inf.readSpace();
        int p = inf.readInt(1, n, "p");
        inf.readSpace();

        if (type == 1) {
            inf.readLong(-2000000000LL, 2000000000LL, "x");
        } else {
            int rangeEnd = inf.readInt(1, n, "q");
            ensuref(p <= rangeEnd, "query %d has p > q: %d > %d", i, p, rangeEnd);
        }
        inf.readEoln();
    }

    inf.readEof();
}
