#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 300000, "N");
    inf.readSpace();
    int q = inf.readInt(1, 300000, "Q");
    inf.readEoln();

    inf.readInts(n, 0, 300000, "A_i");
    inf.readEoln();

    for (int i = 0; i < q; ++i) {
        inf.readInt(1, 300000, "m");
        inf.readEoln();
    }

    inf.readEof();
}
