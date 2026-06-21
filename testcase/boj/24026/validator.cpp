#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 200000, "n");
    inf.readSpace();
    int q = inf.readInt(1, 100000, "q");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        int l = inf.readInt(1, i, "l_i");
        inf.readSpace();
        int r = inf.readInt(i, n, "r_i");
        inf.readEoln();

        ensuref(l <= i && i <= r, "interval %d does not contain its city: [%d, %d]", i, l, r);
    }

    for (int i = 1; i <= q; ++i) {
        inf.readInt(1, n, "u_i");
        inf.readSpace();
        inf.readInt(1, n, "v_i");
        inf.readEoln();
    }

    inf.readEof();
}
