#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int l = inf.readInt(1, 100000, "L");
    inf.readSpace();
    int r = inf.readInt(1, 100000, "R");
    inf.readEoln();

    ensuref(l <= r, "L must be less than or equal to R: L=%d, R=%d", l, r);

    inf.readEof();
}
