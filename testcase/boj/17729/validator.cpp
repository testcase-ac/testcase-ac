#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int kMaxTime = 86400000 - 1;

    int n = inf.readInt(2, 100000, "N");
    inf.readSpace();
    int m = inf.readInt(1, 300000, "M");
    inf.readEoln();

    for (int i = 1; i <= m; ++i) {
        int a = inf.readInt(1, n, "A_i");
        inf.readSpace();
        int b = inf.readInt(1, n, "B_i");
        inf.readSpace();
        int x = inf.readInt(0, kMaxTime, "X_i");
        inf.readSpace();
        int y = inf.readInt(0, kMaxTime, "Y_i");
        inf.readEoln();

        ensuref(a != b, "bus %d has identical endpoints: %d", i, a);
        ensuref(x < y, "bus %d has non-increasing time: %d >= %d", i, x, y);
    }

    int q = inf.readInt(1, 100000, "Q");
    inf.readEoln();

    for (int i = 1; i <= q; ++i) {
        inf.readInt(0, kMaxTime, "L_j");
        inf.readEoln();
    }

    inf.readEof();
}
