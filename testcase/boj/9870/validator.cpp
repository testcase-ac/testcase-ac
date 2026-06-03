#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 200, "N");
    inf.readSpace();
    int m = inf.readInt(1, 10000, "M");
    inf.readSpace();
    int k = inf.readInt(1, 100, "K");
    inf.readSpace();
    int q = inf.readInt(1, 10000, "Q");
    inf.readEoln();

    ensuref(k <= n, "K must be at most N, got K=%d and N=%d", k, n);

    for (int i = 1; i <= m; ++i) {
        inf.readInt(1, n, "u_i");
        inf.readSpace();
        inf.readInt(1, n, "v_i");
        inf.readSpace();
        inf.readInt(1, 1000000, "d_i");
        inf.readEoln();
    }

    for (int i = 1; i <= q; ++i) {
        inf.readInt(1, n, "a_i");
        inf.readSpace();
        inf.readInt(1, n, "b_i");
        inf.readEoln();
    }

    inf.readEof();
}
