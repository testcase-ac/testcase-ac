#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: The statement gives no upper bound for t. Cap both case count and
    // total cells so validation remains practical while preserving input shape.
    const int maxT = 100000;
    const int maxTotalCells = 10000;

    int t = inf.readInt(1, maxT, "t");
    inf.readEoln();

    int totalCells = 0;
    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        inf.readEoln();

        int r = inf.readInt(1, 100, "r");
        inf.readSpace();
        int c = inf.readInt(1, 100, "c");
        inf.readEoln();

        int rr = inf.readInt(1, r, "r_r");
        inf.readSpace();
        int cr = inf.readInt(1, c, "c_r");
        inf.readEoln();

        int rb = inf.readInt(1, r, "r_b");
        inf.readSpace();
        int cb = inf.readInt(1, c, "c_b");
        inf.readEoln();

        ensuref(rr != rb || cr != cb,
                "red and blue cells must be different, both are (%d, %d)",
                rr, cr);

        totalCells += r * c;
        ensuref(totalCells <= maxTotalCells,
                "total rectangle area exceeds %d after test case %d",
                maxTotalCells, tc);
    }

    inf.readEof();
}
