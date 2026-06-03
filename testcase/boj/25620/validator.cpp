#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 200000, "N");
    inf.readSpace();
    int q = inf.readInt(1, 200000, "Q");
    inf.readEoln();

    inf.readInts(n, 0, 1000000000, "a_i");
    inf.readEoln();

    for (int i = 1; i <= q; ++i) {
        inf.readInt(0, 1000000000, "x_i");
        inf.readSpace();
        inf.readInt(0, 1000000000, "y_i");
        inf.readEoln();
    }

    inf.readEof();
}
