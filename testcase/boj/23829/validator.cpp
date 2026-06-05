#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "n");
    inf.readSpace();
    int q = inf.readInt(1, 100000, "q");
    inf.readEoln();

    inf.readInts(n, 1, 10000000, "p_i");
    inf.readEoln();

    for (int i = 1; i <= q; ++i) {
        inf.readInt(1, 10000000, "x_i");
        inf.readEoln();
    }

    inf.readEof();
}
