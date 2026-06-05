#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 10000, "N");
    inf.readSpace();
    int m = inf.readInt(1, 100, "M");
    inf.readEoln();

    inf.readInts(m, 1, 10000, "L_j");
    inf.readEoln();

    for (int i = 1; i <= n - 1; ++i) {
        inf.readInts(m, 1, 10000, "K_i_j");
        inf.readEoln();
    }

    inf.readEof();
}
