#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 5000, "N");
    inf.readSpace();
    int q = inf.readInt(1, 100000, "Q");
    inf.readEoln();

    inf.readInts(n, -1000000, 1000000, "A_i");
    inf.readEoln();

    for (int i = 1; i <= q; ++i) {
        int a = inf.readInt(1, n, "a_i");
        inf.readSpace();
        int b = inf.readInt(a, n, "b_i");
        inf.readEoln();
    }

    inf.readEof();
}
