#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "N");
    inf.readEoln();

    int previousX = -1;
    for (int i = 1; i <= n; ++i) {
        int x = inf.readInt(0, 1000000, "x_i");
        inf.readSpace();
        inf.readInt(1, 1000000, "p_i");
        inf.readEoln();

        ensuref(previousX < x,
                "x_i must be strictly increasing: x_%d=%d, x_%d=%d",
                i - 1, previousX, i, x);
        previousX = x;
    }

    inf.readEof();
}
