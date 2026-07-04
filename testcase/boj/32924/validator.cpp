#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 10000, "t");
    inf.readEoln();

    int totalN = 0;
    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(1, 100000, "n");
        inf.readEoln();

        inf.readInts(n, 1, 1000000, "h_i");
        inf.readEoln();

        inf.readInts(n, 1, 1000000, "p_i");
        inf.readEoln();

        totalN += n;
        ensuref(totalN <= 100000, "sum of n exceeds 100000");
    }

    inf.readEof();
}
