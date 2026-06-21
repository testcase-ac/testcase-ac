#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000000, "N");
    inf.readSpace();
    int m = inf.readInt(1, 1000000, "M");
    inf.readSpace();
    int k = inf.readInt(1, 1000000, "K");
    inf.readEoln();

    inf.readInts(n, 0, 100, "A_i");
    inf.readEoln();

    for (int i = 1; i <= m; ++i) {
        int u = inf.readInt(1, n, "u_i");
        inf.readSpace();
        int v = inf.readInt(1, n, "v_i");
        inf.readSpace();
        inf.readInt(1, 1000, "C_i");
        inf.readEoln();

        // CHECK: The statement does not forbid self-loops or parallel roads.
        // N=1 and M>=1 would otherwise have no valid minimum-sized instance.
        (void)u;
        (void)v;
    }

    for (int i = 1; i <= k; ++i) {
        inf.readInt(1, n, "x_i");
        inf.readEoln();
    }

    inf.readEof();
}
