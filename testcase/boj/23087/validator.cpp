#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 100000, "N");
    inf.readSpace();
    int m = inf.readInt(2, 300000, "M");
    inf.readSpace();
    int x = inf.readInt(1, n, "x");
    inf.readSpace();
    int y = inf.readInt(1, n, "y");
    inf.readEoln();

    ensuref(x != y, "x and y must be different: %d", x);

    for (int i = 1; i <= m; ++i) {
        int u = inf.readInt(1, n, "u");
        inf.readSpace();
        int v = inf.readInt(1, n, "v");
        inf.readSpace();
        inf.readInt(1, 200000, "w");
        inf.readEoln();

        ensuref(u != v, "edge %d has identical endpoints: %d", i, u);
    }

    inf.readEof();
}
