#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "N");
    inf.readSpace();
    int m = inf.readInt(1, 100, "M");
    inf.readSpace();
    inf.readLong(1LL, 1000000000LL, "K");
    inf.readEoln();

    for (int i = 1; i <= m; ++i) {
        int l = inf.readInt(1, n, "L_i");
        inf.readSpace();
        int r = inf.readInt(1, n, "R_i");
        inf.readEoln();

        ensuref(l < r, "L_i must be less than R_i at operation %d: %d >= %d", i, l, r);
    }

    inf.readEof();
}
