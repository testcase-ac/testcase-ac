#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000000, "N");
    inf.readSpace();
    int l = inf.readInt(1, 10000, "L");
    inf.readEoln();

    ensuref(l <= n, "L must be at most N, got L=%d and N=%d", l, n);

    inf.readInts(n, 0, 200, "a_i");
    inf.readEoln();
    inf.readEof();
}
