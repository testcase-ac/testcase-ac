#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 100000, "T");
    inf.readEoln();

    long long totalN = 0;
    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        if (inf.curChar() == '\n') {
            inf.readEoln();
        }

        int n = inf.readInt(1, 100000, "N");
        inf.readEoln();

        totalN += n;
        // CHECK: T has no statement maximum; cap total list length to keep inputs under about 5M scalar tokens.
        ensuref(totalN <= 2000000, "sum of N exceeds practical cap: %lld", totalN);

        inf.readInts(n, 1, 1000000, "cornell_id");
        inf.readEoln();

        inf.readInts(n, 1, 1000000, "white_id");
        inf.readEoln();
    }

    inf.readEof();
}
