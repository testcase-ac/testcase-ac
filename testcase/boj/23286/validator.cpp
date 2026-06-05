#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 300, "N");
    inf.readSpace();
    int m = inf.readInt(1, 25000, "M");
    inf.readSpace();
    int t = inf.readInt(1, 40000, "T");
    inf.readEoln();

    for (int i = 1; i <= m; ++i) {
        int u = inf.readInt(1, n, "u");
        inf.readSpace();
        int v = inf.readInt(1, n, "v");
        inf.readSpace();
        inf.readInt(1, 1000000, "h");
        inf.readEoln();

        ensuref(u != v, "edge %d is a self-loop at vertex %d", i, u);
    }

    for (int i = 1; i <= t; ++i) {
        int s = inf.readInt(1, n, "s");
        inf.readSpace();
        int e = inf.readInt(1, n, "e");
        inf.readEoln();

        ensuref(s != e, "query %d has identical endpoints: %d", i, s);
    }

    inf.readEof();
}
