#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "N");
    inf.readSpace();
    int m = inf.readInt(0, 200000, "M");
    inf.readSpace();
    int q = inf.readInt(1, 100000, "Q");
    inf.readEoln();

    inf.readInts(n, 0, 1, "water_i");
    inf.readEoln();

    for (int i = 1; i <= m; ++i) {
        int u = inf.readInt(1, n, "u");
        inf.readSpace();
        int v = inf.readInt(1, n, "v");
        inf.readEoln();

        ensuref(u != v, "pipe %d is a self-loop at tank %d", i, u);
    }

    for (int i = 1; i <= q; ++i) {
        inf.readInt(1, n, "K");
        inf.readEoln();
    }

    inf.readEof();
}
