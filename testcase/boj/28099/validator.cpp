#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 200000, "T");
    inf.readEoln();

    long long sumN = 0;
    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(1, 200000, "N");
        inf.readEoln();

        sumN += n;
        ensuref(sumN <= 200000, "sum of N exceeds 200000");

        inf.readInts(n, 1, n, "A_i");
        inf.readEoln();
    }

    inf.readEof();
}
