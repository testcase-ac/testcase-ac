#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int s = inf.readInt(1, 1000000, "S");
    inf.readSpace();
    int c = inf.readInt(1, 1000000, "C");
    inf.readEoln();

    ensuref(s <= c, "S must not exceed C: S=%d, C=%d", s, c);

    for (int i = 0; i < s; ++i) {
        inf.readInt(1, 1000000000, "L");
        inf.readEoln();
    }

    inf.readEof();
}
