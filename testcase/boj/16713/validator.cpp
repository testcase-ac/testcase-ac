#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000000, "N");
    inf.readSpace();
    int q = inf.readInt(1, 3000000, "Q");
    inf.readEoln();

    inf.readInts(n, 0, 1000000000, "a_i");
    inf.readEoln();

    for (int i = 1; i <= q; ++i) {
        int s = inf.readInt(1, n, "s_i");
        inf.readSpace();
        int e = inf.readInt(s, n, "e_i");
        inf.readEoln();
    }

    inf.readEof();
}
