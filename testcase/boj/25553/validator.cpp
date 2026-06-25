#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 200000, "N");
    inf.readSpace();
    int q = inf.readInt(1, 200000, "Q");
    inf.readSpace();
    inf.readInt(1, n, "K");
    inf.readEoln();

    inf.readInts(n, -100000, 100000, "A_i");
    inf.readEoln();

    bool hasQuery = false;
    for (int i = 1; i <= q; ++i) {
        int t = inf.readInt(1, 3, "t");
        if (t == 3) {
            hasQuery = true;
            inf.readEoln();
        } else {
            inf.readSpace();
            inf.readInt(-100000, 100000, "x");
            inf.readEoln();
        }
    }

    ensuref(hasQuery, "at least one operation of type 3 is required");
    inf.readEof();
}
