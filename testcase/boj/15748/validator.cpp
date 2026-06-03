#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int l = inf.readInt(1, 1000000, "L");
    inf.readSpace();
    int n = inf.readInt(1, 100000, "N");
    inf.readSpace();
    int r_f = inf.readInt(1, 1000000, "r_F");
    inf.readSpace();
    int r_b = inf.readInt(1, 1000000, "r_B");
    inf.readEoln();

    ensuref(r_f > r_b, "expected r_F > r_B, got r_F=%d and r_B=%d", r_f, r_b);

    int previous_x = 0;
    for (int i = 1; i <= n; ++i) {
        int x = inf.readInt(1, l - 1, "x_i");
        inf.readSpace();
        inf.readInt(1, 1000000, "c_i");
        inf.readEoln();

        ensuref(previous_x < x, "expected x_%d < x_%d, got %d and %d",
                i - 1, i, previous_x, x);
        previous_x = x;
    }

    inf.readEof();
}
