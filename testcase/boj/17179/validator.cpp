#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000, "N");
    inf.readSpace();
    int m = inf.readInt(n, 1000, "M");
    inf.readSpace();
    int l = inf.readInt(2, 4000000, "L");
    inf.readEoln();

    int previous = 0;
    for (int i = 1; i <= m; ++i) {
        int s = inf.readInt(1, l - 1, "S_i");
        inf.readEoln();
        ensuref(previous < s, "S_i must be strictly increasing: S_%d=%d, S_%d=%d",
                i - 1, previous, i, s);
        previous = s;
    }

    previous = 0;
    for (int i = 1; i <= n; ++i) {
        int q = inf.readInt(1, m, "Q_i");
        inf.readEoln();
        ensuref(previous < q, "Q_i must be strictly increasing: Q_%d=%d, Q_%d=%d",
                i - 1, previous, i, q);
        previous = q;
    }

    inf.readEof();
}
