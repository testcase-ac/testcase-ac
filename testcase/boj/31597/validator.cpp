#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 1000, "t");
    inf.readEoln();

    int sumN2 = 0;
    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(3, 100, "n");
        inf.readEoln();

        sumN2 += n * n;
        ensuref(sumN2 <= 10000, "sum of n^2 exceeds 10000");

        for (int i = 1; i <= n; ++i) {
            inf.readInts(n, 1, n, "X_i_j");
            inf.readEoln();
        }
    }

    inf.readEof();
}
