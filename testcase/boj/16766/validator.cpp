#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "N");
    inf.readSpace();
    int m = inf.readInt(1, 100000, "M");
    inf.readSpace();
    int c = inf.readInt(1, n, "C");
    inf.readEoln();

    ensuref(1LL * m * c >= n, "M * C must be at least N: M=%d C=%d N=%d", m, c, n);

    inf.readInts(n, 0, 1000000000, "t_i");
    inf.readEoln();
    inf.readEof();
}
