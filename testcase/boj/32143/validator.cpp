#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(1, 1000000000, "H");
    inf.readEoln();

    int n = inf.readInt(1, 300000, "N");
    inf.readSpace();
    int q = inf.readInt(1, 300000, "Q");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        if (i > 0) {
            inf.readSpace();
        }
        inf.readInt(1, 1000000000, "D_i");
    }
    inf.readEoln();

    for (int i = 0; i < q; ++i) {
        inf.readInt(1, 1000000000, "x");
        inf.readEoln();
    }

    inf.readEof();
}
