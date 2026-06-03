#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    for (int i = 0; i < 3; ++i) {
        int c = inf.readInt(1, 1000, "C");
        inf.readSpace();
        int d = inf.readInt(1, 1000, "D");
        inf.readEoln();
        ensuref(c <= d, "C must be at most D on skill line %d: C=%d, D=%d", i + 1, c, d);
    }

    inf.readInt(1, 5000, "H");
    inf.readEoln();
    inf.readEof();
}
