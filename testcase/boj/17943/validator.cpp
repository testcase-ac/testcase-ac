#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int maxN = 200000;
    const int maxQ = 100000;
    const int maxValue = 2147483647;

    int n = inf.readInt(3, maxN, "N");
    inf.readSpace();
    int q = inf.readInt(1, maxQ, "Q");
    inf.readEoln();

    for (int i = 1; i < n; ++i) {
        if (i > 1) {
            inf.readSpace();
        }
        inf.readInt(0, maxValue, "a_i");
    }
    inf.readEoln();

    for (int i = 1; i <= q; ++i) {
        int type = inf.readInt(0, 1, "type");
        inf.readSpace();
        int x = inf.readInt(1, n, "x");
        inf.readSpace();
        int y = inf.readInt(x, n, "y");

        if (type == 1) {
            inf.readSpace();
            inf.readInt(0, maxValue, "d");
        }
        inf.readEoln();
    }

    inf.readEof();
}
