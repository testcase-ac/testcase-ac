#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(1, 100000000, "W");
    inf.readSpace();
    inf.readInt(1, 1000000, "v_h");
    inf.readSpace();
    int n = inf.readInt(1, 100000, "N");
    inf.readEoln();

    int previousY = 0;
    for (int i = 1; i <= n; ++i) {
        inf.readInt(1, 100000000, "x_i");
        inf.readSpace();
        int y = inf.readInt(1, 100000000, "y_i");
        inf.readEoln();

        ensuref(i == 1 || previousY < y,
                "gate y-coordinates must be strictly increasing: y_%d=%d, y_%d=%d",
                i - 1, previousY, i, y);
        previousY = y;
    }

    int s = inf.readInt(1, 1000000, "S");
    inf.readEoln();

    for (int i = 1; i <= s; ++i) {
        inf.readInt(1, 1000000, "s_j");
        inf.readEoln();
    }

    inf.readEof();
}
