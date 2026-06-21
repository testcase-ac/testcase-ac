#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int maxT = 100000;
    const int maxN = 100000;
    const int maxK = 1000000;
    const int maxAi = 100000;
    const int maxTotalN = 4999999;

    int t = inf.readInt(1, maxT, "T");
    inf.readEoln();

    long long totalN = 0;
    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(1, maxN, "N");
        inf.readSpace();
        inf.readInt(1, maxK, "K");
        inf.readEoln();

        totalN += n;
        // CHECK: The statement has no aggregate bound across test cases; keep numeric input below the local practical token cap.
        ensuref(totalN <= maxTotalN, "total N exceeds practical cap: %lld", totalN);

        inf.readInts(n, 1, maxAi, "A_i");
        inf.readEoln();
    }

    inf.readEof();
}
