#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int x = inf.readInt(1, 99, "x");
    inf.readEoln();
    int m = inf.readInt(2, 100, "m");
    inf.readEoln();
    ensuref(x < m, "expected x < m, got x=%d and m=%d", x, m);

    inf.readEof();
}
