#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "N");
    inf.readSpace();
    int q = inf.readInt(1, 100000, "Q");
    inf.readEoln();

    inf.readInts(n, 1, 1000000, "a_i");
    inf.readEoln();

    for (int i = 1; i <= q; ++i) {
        int t = inf.readInt(1, 2, "T");
        inf.readSpace();
        int s = inf.readInt(1, n, "S");
        inf.readSpace();
        int e = inf.readInt(s, n, "E");
        inf.readEoln();
    }

    inf.readEof();
}
