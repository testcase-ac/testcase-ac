#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100, "N");
    inf.readSpace();
    int x = inf.readInt(1, 10000, "x");
    inf.readEoln();

    int previousLength = 0;
    for (int i = 1; i <= n; ++i) {
        int length = inf.readInt(1, x, "L_i");
        inf.readSpace();
        inf.readInt(1, 100, "C_i");
        inf.readEoln();

        ensuref(previousLength < length,
                "pipe lengths must be strictly increasing: L_%d=%d after %d",
                i, length, previousLength);
        previousLength = length;
    }

    inf.readEof();
}
