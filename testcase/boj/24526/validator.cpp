#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 100000, "N");
    inf.readSpace();
    int m = inf.readInt(1, 500000, "M");
    inf.readEoln();

    for (int i = 1; i <= m; ++i) {
        int u = inf.readInt(1, n, "U_i");
        inf.readSpace();
        int v = inf.readInt(1, n, "V_i");
        inf.readEoln();

        ensuref(u != v, "self-loop at relation %d: %d -> %d", i, u, v);
    }

    inf.readEof();
}
