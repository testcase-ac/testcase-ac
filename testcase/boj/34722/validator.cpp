#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100, "N");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        inf.readInt(0, 100000, "s_i");
        inf.readSpace();
        inf.readInt(0, 4000, "c_i");
        inf.readSpace();
        inf.readInt(0, 4000, "a_i");
        inf.readSpace();

        int r = inf.readInt(-1, 200, "r_i");
        ensuref(r == -1 || r >= 1, "r_%d must be -1 or between 1 and 200, got %d", i, r);
        inf.readEoln();
    }

    inf.readEof();
}
