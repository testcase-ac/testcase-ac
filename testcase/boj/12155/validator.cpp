#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int T = inf.readInt(1, 1000, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);

        int R = inf.readInt(1, 16, "R");
        inf.readSpace();
        int C = inf.readInt(1, 16, "C");
        inf.readSpace();
        int N = inf.readInt(0, 16, "N");
        inf.readEoln();

        int cells = R * C;
        ensuref(cells <= 16, "case %d has R*C = %d, exceeding 16", tc, cells);
        ensuref(N <= cells, "case %d has N = %d, exceeding R*C = %d", tc, N, cells);
    }

    inf.readEof();
    return 0;
}
