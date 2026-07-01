#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int T = inf.readInt(1, 1000, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);

        int R = inf.readInt(1, 10000, "R");
        inf.readSpace();
        int C = inf.readInt(1, 10000, "C");
        inf.readSpace();
        int N = inf.readInt(0, 10000, "N");
        inf.readEoln();

        int cells = R * C;
        ensuref(cells <= 10000, "R*C must be at most 10000, got %d", cells);
        ensuref(N <= cells, "N must be at most R*C, got N=%d and R*C=%d", N, cells);
    }

    inf.readEof();
}
