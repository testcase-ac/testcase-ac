#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100, "N");
    inf.readSpace();
    int q = inf.readInt(1, 200000, "Q");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        inf.readInt(1, 10000, "P_i");
        inf.readSpace();
        inf.readInt(1, 10000, "L_i");
        inf.readEoln();
    }

    for (int j = 1; j <= q; ++j) {
        inf.readInt(1, 1000000, "A_j");
        inf.readSpace();
        inf.readInt(1, 1000000, "B_j");
        inf.readEoln();
    }

    inf.readEof();
}
