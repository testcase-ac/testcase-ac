#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int maxTotalQueries = 100000;
    int totalQueries = 0;

    for (int tc = 1;; ++tc) {
        int n = inf.readInt(0, 26, "n");
        inf.readSpace();
        int q = inf.readInt(0, 1000, "q");
        inf.readEoln();

        if (n == 0 && q == 0) {
            break;
        }

        setTestCase(tc);
        ensuref(1 <= n && n <= 26, "n must be in [1, 26], got %d", n);
        ensuref(1 <= q && q <= 1000, "q must be in [1, 1000], got %d", q);

        // CHECK: the statement does not bound the number of test cases; cap total
        // queries to keep generated validation inputs practical.
        totalQueries += q;
        ensuref(totalQueries <= maxTotalQueries,
                "total number of queries exceeds %d", maxTotalQueries);

        for (int i = 0; i < n; ++i) {
            if (i > 0) {
                inf.readSpace();
            }
            inf.readToken("[A-Za-z0-9]{1,100}", "title");
        }
        inf.readEoln();

        for (int i = 0; i < q; ++i) {
            if (i > 0) {
                inf.readSpace();
            }
            inf.readInt(1, 100000000, "k");
        }
        inf.readEoln();
    }

    inf.readEof();
}
