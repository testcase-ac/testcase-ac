#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int maxN = 100000;
    const int maxQ = 50000;
    const int maxValue = 10000000;

    int n = inf.readInt(1, maxN, "n");
    inf.readEoln();

    inf.readInts(n, 0, maxValue, "a");
    inf.readEoln();

    int q = inf.readInt(1, maxQ, "q");
    inf.readEoln();

    for (int i = 1; i <= q; ++i) {
        int type = inf.readInt(1, 3, "type");
        inf.readSpace();

        if (type == 1 || type == 2) {
            int l = inf.readInt(1, n, "l");
            inf.readSpace();
            int r = inf.readInt(l, n, "r");
            inf.readSpace();
            inf.readInt(0, maxValue, "x");
        } else {
            inf.readInt(1, n, "p");
            inf.readSpace();
            inf.readInt(0, maxValue, "x");
        }

        inf.readEoln();
    }

    inf.readEof();
}
