#include "testlib.h"

#include <cstdint>

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 100000, "T");
    inf.readEoln();

    long long totalN = 0;
    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(2, 100000, "N");
        inf.readSpace();
        int k = inf.readInt(1, 20, "K");
        inf.readEoln();

        totalN += n;
        // CHECK: T is unbounded in the statement; cap total N to keep inputs practical.
        ensuref(totalN <= 1000000, "total N exceeds practical cap: %lld", totalN);

        for (int i = 1; i <= n; ++i) {
            inf.readInt(1, 2147483647, "S_i");
            if (i == n) {
                inf.readEoln();
            } else {
                inf.readSpace();
            }
        }
    }

    inf.readEof();
}
