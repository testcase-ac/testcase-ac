#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int q = inf.readInt(1, 500000, "Q");
    inf.readEoln();

    for (int i = 1; i <= q; ++i) {
        int l = inf.readInt(2, 499999, "L");
        inf.readSpace();
        int r = inf.readInt(l + 1, 500000, "R");
        inf.readEoln();
    }

    inf.readEof();
}
