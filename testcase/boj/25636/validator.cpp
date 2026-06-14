#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 100000, "n");
    inf.readEoln();

    inf.readInts(n, 1, 1000000, "a");
    inf.readEoln();

    int m = inf.readInt(1, 300000, "m");
    inf.readEoln();

    for (int i = 1; i <= m; ++i) {
        int u = inf.readInt(1, n, "u");
        inf.readSpace();
        int v = inf.readInt(1, n, "v");
        inf.readSpace();
        inf.readInt(1, 1000000, "w");
        inf.readEoln();

        ensuref(u != v, "edge %d is a self-loop at vertex %d", i, u);
    }

    int s = inf.readInt(1, n, "s");
    inf.readSpace();
    int t = inf.readInt(1, n, "t");
    inf.readEoln();

    ensuref(s != t, "s and t must be distinct: %d", s);

    inf.readEof();
}
