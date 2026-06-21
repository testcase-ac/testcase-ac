#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(3, 1000, "n");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        int x = inf.readInt(1, n, "x_i");
        inf.readSpace();
        int y = inf.readInt(1, n, "y_i");
        inf.readEoln();

        ensuref(x != i, "x_%d must not be equal to %d", i, i);
        ensuref(y != i, "y_%d must not be equal to %d", i, i);
        ensuref(x != y, "x_%d and y_%d must be distinct", i, i);
    }

    inf.readEof();
}
