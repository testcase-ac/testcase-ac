#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 200000, "N");
    inf.readSpace();
    int k = inf.readInt(1, 200000, "K");
    inf.readSpace();
    int m = inf.readInt(1, 200000, "M");
    inf.readEoln();

    ensuref(k <= m, "K must be at most M: K=%d M=%d", k, m);

    inf.readInts(n, 1, 200000, "A_i");
    inf.readEoln();

    inf.readInts(m, 0, 200000, "D_i");
    inf.readEoln();

    inf.readEof();
}
