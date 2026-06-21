#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "N");
    inf.readEoln();

    inf.readInts(n, 0, 1000000, "A_i");
    inf.readEoln();

    int q = inf.readInt(1, 100000, "Q");
    inf.readEoln();

    for (int i = 1; i <= q; ++i) {
        int l = inf.readInt(1, n, "L");
        inf.readSpace();
        int r = inf.readInt(l, n, "R");
        inf.readSpace();
        inf.readInt(0, 1000000, "x");
        inf.readEoln();
    }

    inf.readEof();
}
