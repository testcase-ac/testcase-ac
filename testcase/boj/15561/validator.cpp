#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "N");
    inf.readSpace();
    int q = inf.readInt(1, 100000, "Q");
    inf.readSpace();
    inf.readInt(-5, 5, "U");
    inf.readSpace();
    inf.readInt(-5, 5, "V");
    inf.readEoln();

    inf.readInts(n, -100, 100, "K_i");
    inf.readEoln();

    for (int query = 1; query <= q; ++query) {
        int c = inf.readInt(0, 1, "C");
        inf.readSpace();

        if (c == 0) {
            int a = inf.readInt(1, n, "A");
            inf.readSpace();
            int b = inf.readInt(a, n, "B");
            inf.readEoln();
        } else {
            inf.readInt(1, n, "A");
            inf.readSpace();
            inf.readInt(-100, 100, "B");
            inf.readEoln();
        }
    }

    inf.readEof();
}
