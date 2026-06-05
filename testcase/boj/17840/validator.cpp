#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int q = inf.readInt(1, 100000, "Q");
    inf.readSpace();
    int m = inf.readInt(2, 1000, "M");
    inf.readEoln();

    for (int i = 1; i <= q; ++i) {
        inf.readLong(1LL, 1000000000000000LL, "N");
        inf.readEoln();
    }

    inf.readEof();
}
