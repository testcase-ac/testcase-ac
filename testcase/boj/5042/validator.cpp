#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(4, 2000, "N");
    inf.readEoln();
    ensuref(n % 2 == 0, "N must be even, found %d", n);

    int l = inf.readInt(1, 10000, "L");
    inf.readSpace();
    inf.readInt(1, 20, "W");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        inf.readInt(0, l, "p_i");
        inf.readEoln();
    }

    inf.readEof();
}
