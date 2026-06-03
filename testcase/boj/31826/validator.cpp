#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "N");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        int p = inf.readInt(7000, 13000, "p_i");
        inf.readSpace();
        inf.readInt(1, 1000, "x_i");
        inf.readSpace();
        int f = inf.readInt(-1, 1, "f_i");
        inf.readEoln();

        ensuref(p % 10 == 0, "p_%d must be a multiple of 10, got %d", i, p);
        ensuref(f == -1 || f == 1, "f_%d must be -1 or 1, got %d", i, f);
    }

    inf.readEof();
}
