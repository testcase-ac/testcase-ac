#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "N");
    inf.readEoln();

    inf.readInts(n, 1, 1000000, "H_i");
    inf.readEoln();

    int q = inf.readInt(1, 100000, "Q");
    inf.readEoln();

    for (int i = 1; i <= q; ++i) {
        inf.readInt(1, n, "p");
        inf.readEoln();
    }

    inf.readEof();
}
