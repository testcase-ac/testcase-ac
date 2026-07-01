#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000, "N");
    inf.readSpace();
    int m = inf.readInt(1, 1000, "M");
    inf.readEoln();

    inf.readInts(n, 0, (1 << 29) - 1, "V_i");
    inf.readEoln();

    inf.readInts(m, 0, (1 << 29) - 1, "U_j");
    inf.readEoln();

    inf.readEof();
}
