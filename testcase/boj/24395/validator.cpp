#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "N");
    inf.readSpace();
    int m = inf.readInt(1, 100, "M");
    inf.readEoln();

    for (int i = 1; i <= m; ++i) {
        int r = inf.readInt(0, 50, "R_i");
        inf.readSpace();
        int b = inf.readInt(0, 50, "B_i");
        inf.readSpace();
        inf.readInt(0, 100, "D_i");
        inf.readEoln();

        ensuref(r + b >= 1, "disease %d has no prescribed pills", i);
    }

    for (int i = 1; i <= n; ++i) {
        int r = inf.readInt(0, 50, "R'_i");
        inf.readSpace();
        int b = inf.readInt(0, 50, "B'_i");
        inf.readEoln();

        ensuref(r + b >= 1, "student %d has no prescribed pills", i);
    }

    inf.readEof();
}
