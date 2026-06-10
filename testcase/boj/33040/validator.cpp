#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int h = inf.readInt(1, 100000, "H");
    inf.readSpace();
    int w = inf.readInt(1, 100000, "W");
    inf.readEoln();

    long long cells = 1LL * h * w;
    ensuref(cells <= 100000LL, "H * W must be at most 100000, got %lld", cells);

    int c = inf.readInt(0, 100000, "C");
    inf.readSpace();
    int d = inf.readInt(0, 100000, "D");
    inf.readEoln();

    ensuref(1LL * c + d == cells, "C + D must equal H * W, got %d + %d != %lld", c, d, cells);

    inf.readEof();
}
