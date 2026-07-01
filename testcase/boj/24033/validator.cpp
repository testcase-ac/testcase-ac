#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 200000, "N");
    inf.readSpace();
    int l = inf.readInt(1, 1000000000, "L");
    inf.readSpace();
    int r = inf.readInt(1, 1000000000, "R");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        int x = inf.readInt(-1000000000, 1000000000, "x_i");
        inf.readSpace();
        int d = inf.readInt(-1, 1, "d_i");
        inf.readSpace();
        inf.readInt(1, 1000000000, "w_i");
        inf.readEoln();

        ensuref(x != 0, "x_%d must not be zero", i);
        ensuref((-l <= x && x <= -1) || (1 <= x && x <= r),
                "x_%d=%d is outside [-L,-1] or [1,R]", i, x);
        ensuref(d == -1 || d == 1, "d_%d must be -1 or 1", i);
    }

    inf.readEof();
}
