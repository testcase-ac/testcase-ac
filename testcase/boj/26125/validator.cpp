#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 300, "n");
    inf.readSpace();
    int m = inf.readInt(0, 3000, "m");
    inf.readSpace();
    int s = inf.readInt(1, n, "s");
    inf.readSpace();
    int t = inf.readInt(1, n, "t");
    inf.readEoln();
    ensuref(s != t, "s and t must be different: %d", s);

    for (int i = 1; i <= m; ++i) {
        inf.readInt(1, n, "u");
        inf.readSpace();
        inf.readInt(1, n, "v");
        inf.readSpace();
        inf.readInt(1, 1000000, "w");
        inf.readEoln();
    }

    int q = inf.readInt(1, 100000, "q");
    inf.readEoln();

    for (int i = 1; i <= q; ++i) {
        inf.readInt(1, n, "a1");
        inf.readSpace();
        inf.readInt(1, n, "b1");
        inf.readSpace();
        inf.readInt(1, 1000000, "c1");
        inf.readSpace();
        inf.readInt(1, n, "a2");
        inf.readSpace();
        inf.readInt(1, n, "b2");
        inf.readSpace();
        inf.readInt(1, 1000000, "c2");
        inf.readEoln();
    }

    inf.readEof();
}
