#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(3, 2000, "N");
    inf.readSpace();
    int m = inf.readInt(1, 100000, "M");
    inf.readSpace();
    inf.readInt(1, 100000, "L");
    inf.readEoln();

    inf.readInts(n, 1, m, "K_i");
    inf.readEoln();

    inf.readInts(m, 1, 100000, "S_j");
    inf.readEoln();

    inf.readEof();
}
