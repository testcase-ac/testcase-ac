#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000000, "N");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        inf.readInt(1, 3, "A_i");
        if (i == n) {
            inf.readEoln();
        } else {
            inf.readSpace();
        }
    }

    int u = inf.readInt(0, n, "U");
    inf.readSpace();
    int d = inf.readInt(0, n, "D");
    inf.readEoln();

    ensuref(u + d == n, "U + D must equal N: U=%d D=%d N=%d", u, d, n);

    inf.readEof();
}
