#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int tests = inf.readInt(1, 100, "T");
    inf.readEoln();

    int totalN = 0;
    for (int t = 1; t <= tests; ++t) {
        setTestCase(t);

        int n = inf.readInt(1, 100000, "N");
        inf.readEoln();
        totalN += n;
        ensuref(totalN <= 1000000, "sum of N must not exceed 1000000");

        int previousX = 0;
        for (int i = 1; i <= n; ++i) {
            int x = inf.readInt(1, 100000000, "x_i");
            inf.readSpace();
            inf.readInt(1, 100000000, "h_i");
            inf.readEoln();
            ensuref(previousX < x,
                    "x coordinates must be strictly increasing: x_%d=%d, x_%d=%d",
                    i - 1, previousX, i, x);
            previousX = x;
        }
    }

    inf.readEof();
}
