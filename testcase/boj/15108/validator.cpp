#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(0, 100, "n");
    inf.readSpace();
    int x = inf.readInt(1, 1000000, "X");
    inf.readSpace();
    inf.readDouble(1.0, 100.0, "v");
    inf.readEoln();

    int previousRight = 0;
    for (int i = 0; i < n; ++i) {
        int left = inf.readInt(0, x, "l_i");
        inf.readSpace();
        int right = inf.readInt(0, x, "r_i");
        inf.readSpace();
        inf.readDouble(-100.0, 100.0, "v_i");
        inf.readEoln();

        ensuref(previousRight <= left,
                "sidewalk %d starts before previous sidewalk ends: previous r=%d, l=%d",
                i + 1, previousRight, left);
        ensuref(left < right,
                "sidewalk %d must have l_i < r_i: l=%d, r=%d",
                i + 1, left, right);
        previousRight = right;
    }

    inf.readEof();
}
