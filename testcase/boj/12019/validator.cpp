#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100, "N");
    inf.readSpace();
    int m = inf.readInt(1, 10, "M");
    inf.readEoln();

    ensuref(m <= n, "M must not exceed N: M=%d, N=%d", m, n);

    inf.readInts(n, 1, 20, "P_i");
    inf.readEoln();
    inf.readEof();
}
