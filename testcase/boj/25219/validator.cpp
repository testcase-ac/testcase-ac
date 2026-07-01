#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 3000, "N");
    inf.readSpace();
    int k = inf.readInt(2, n, "K");
    inf.readSpace();
    int q = inf.readInt(1, 1000000, "Q");
    inf.readEoln();

    inf.readInts(n, 1, k, "A_i");
    inf.readEoln();

    for (int i = 0; i < q; ++i) {
        int x = inf.readInt(1, n - 1, "x");
        inf.readSpace();
        inf.readInt(x + 1, n, "y");
        inf.readEoln();
    }

    inf.readEof();
}
