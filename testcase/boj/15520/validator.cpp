#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int l = inf.readInt(1, 1000000000, "l");
    inf.readSpace();
    int r = inf.readInt(l, 1000000000, "r");
    inf.readEoln();

    ensuref(r - l < 1000000, "interval width must be less than 1000000: l=%d r=%d", l, r);

    inf.readEof();
}
