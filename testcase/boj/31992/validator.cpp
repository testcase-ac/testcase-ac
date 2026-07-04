#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 15, "N");
    inf.readSpace();
    int m = inf.readInt(1, 1000, "M");
    inf.readEoln();

    inf.readInts(m, 1, 10000000, "c_j");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        inf.readInts(m, 0, 10000000, "r_i_j");
        inf.readEoln();
    }

    inf.readEof();
}
