#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: The statement does not bound T; cap total stations at one largest
    // testcase so validation remains within the stated N scale.
    const int maxT = 100000;
    const int maxTotalN = 1000000;

    int t = inf.readInt(1, maxT, "T");
    inf.readEoln();

    int totalN = 0;
    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(3, 1000000, "N");
        inf.readEoln();
        totalN += n;
        ensuref(totalN <= maxTotalN, "sum of N exceeds %d", maxTotalN);

        for (int i = 1; i <= n; ++i) {
            inf.readInt(0, 512, "G");
            inf.readSpace();
            inf.readInt(1, 512, "D");
            inf.readEoln();
        }
    }

    inf.readEof();
}
