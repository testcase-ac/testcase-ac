#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int maxN = 200000;
    const int maxQ = 200000;
    const int maxValue = (1 << 31) - 1;

    int n = inf.readInt(1, maxN, "N");
    inf.readEoln();

    inf.readInts(n, 0, maxValue, "A_i");
    inf.readEoln();

    int q = inf.readInt(1, maxQ, "Q");
    inf.readEoln();

    bool hasTypeOneQuery = false;
    for (int queryIndex = 1; queryIndex <= q; ++queryIndex) {
        int type = inf.readInt(1, 2, "type");
        inf.readSpace();

        if (type == 1) {
            hasTypeOneQuery = true;
            int l = inf.readInt(0, n - 1, "l");
            inf.readSpace();
            int r = inf.readInt(l, n - 1, "r");
            inf.readSpace();
            inf.readInt(0, n - 1, "x");
        } else {
            inf.readInt(0, n - 1, "i");
            inf.readSpace();
            inf.readInt(0, maxValue, "x");
        }

        inf.readEoln();
    }

    ensuref(hasTypeOneQuery, "input must contain at least one type 1 query");

    inf.readEof();
}
