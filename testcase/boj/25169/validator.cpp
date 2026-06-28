#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100, "N");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        int r = inf.readInt(1, 100, "R_i");
        inf.readSpace();
        int s = inf.readInt(10, 10000, "S_i");
        ensuref(s % 10 == 0, "S_%d must be a multiple of 10, found %d", i, s);
        inf.readEoln();
    }

    inf.readEof();
}
