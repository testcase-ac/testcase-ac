#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int q = inf.readInt(1, 100000, "Q");
    inf.readEoln();

    for (int i = 1; i <= q; ++i) {
        inf.readLong(-1000000000LL, 1000000000LL, "x");
        inf.readSpace();
        inf.readLong(-1000000000LL, 1000000000LL, "y");
        inf.readEoln();
    }

    inf.readEof();
}
