#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int n = inf.readInt(1, 500000, "N");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        const int a = inf.readInt(0, n, "A_i");
        inf.readSpace();
        const int b = inf.readInt(a, n, "B_i");
        inf.readEoln();
    }

    const int q = inf.readInt(1, 500000, "Q");
    inf.readEoln();

    for (int i = 1; i <= q; ++i) {
        const int p = inf.readInt(1, n, "P_i");
        inf.readSpace();
        const int l = inf.readInt(0, n, "L_i");
        inf.readSpace();
        const int r = inf.readInt(l, n, "R_i");
        inf.readEoln();
    }

    inf.readEof();
}
