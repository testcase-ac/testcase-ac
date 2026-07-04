#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int sunLimit = inf.readInt(0, 3600, "S");
    inf.readEoln();

    int n = inf.readInt(2, 1600, "N");
    inf.readSpace();
    int e = inf.readInt(1, 10000, "E");
    inf.readEoln();

    for (int i = 0; i < e; ++i) {
        int s = inf.readInt(0, n - 1, "s");
        inf.readSpace();
        int t = inf.readInt(0, n - 1, "t");
        inf.readSpace();
        int d = inf.readInt(1, 10000, "d");
        inf.readSpace();
        int u = inf.readInt(0, 1, "u");
        inf.readEoln();

        ensuref(s != t, "connection %d has identical endpoints %d", i + 1, s);
        (void)d;
        (void)u;
    }

    (void)sunLimit;
    inf.readEof();
}
