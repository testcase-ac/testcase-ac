#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 30000, "n");
    inf.readSpace();
    int l = inf.readInt(1, n, "l");
    inf.readSpace();
    int h = inf.readInt(l, n, "h");
    inf.readEoln();

    ensuref(h - l <= 1000, "h - l must be at most 1000, got %d", h - l);

    for (int i = 0; i < n; ++i) {
        inf.readInt(-10000, 10000, "p_i");
        inf.readEoln();
    }

    inf.readEof();
}
