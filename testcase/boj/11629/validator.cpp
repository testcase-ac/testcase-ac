#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: The statement does not specify an upper bound for T; use the local
    // practical cap for multi-case numeric input.
    int t = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(2, 5000, "N");
        inf.readEoln();

        int x1 = inf.readInt(1, n, "X1");
        inf.readSpace();
        int y1 = inf.readInt(1, n, "Y1");
        inf.readSpace();
        int x2 = inf.readInt(1, n, "X2");
        inf.readSpace();
        int y2 = inf.readInt(1, n, "Y2");
        inf.readEoln();

        ensuref(x1 != x2 || y1 != y2,
                "case %d has identical start and destination: (%d, %d)",
                tc,
                x1,
                y1);
    }

    inf.readEof();
}
