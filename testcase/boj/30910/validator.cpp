#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 20000, "T");
    inf.readEoln();

    long long totalN = 0;
    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(1, 1000000, "N");
        inf.readEoln();

        totalN += n;
        ensuref(totalN <= 1000000, "sum of N exceeds 1000000");

        inf.readInts(n, 0, 3, "A_i");
        inf.readEoln();
    }

    inf.readEof();
}
