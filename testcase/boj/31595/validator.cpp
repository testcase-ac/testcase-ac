#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 1000, "t");
    inf.readEoln();

    long long totalN = 0;
    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(1, 500000, "n");
        inf.readEoln();

        totalN += n;
        ensuref(totalN <= 500000, "sum of n exceeds 500000");

        inf.readInts(n, 0, 60, "a_i");
        inf.readEoln();
    }

    inf.readEof();
}
