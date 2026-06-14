#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: The statement gives no upper bound for the number of datasets.
    int t = inf.readInt(1, 100000, "t");
    inf.readEoln();

    for (int i = 1; i <= t; ++i) {
        setTestCase(i);

        int m = inf.readInt(-141, 141, "m");
        inf.readSpace();
        int n = inf.readInt(-141, 141, "n");
        inf.readEoln();

        int norm = m * m + n * n;
        ensuref(1 < norm && norm < 20000,
                "m^2 + n^2 must satisfy 1 < value < 20000, got %d", norm);
    }

    inf.readEof();
}
