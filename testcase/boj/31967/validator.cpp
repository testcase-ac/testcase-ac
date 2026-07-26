#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 250000, "n");
    inf.readSpace();
    int q = inf.readInt(1, 250000, "q");
    inf.readEoln();

    inf.readInts(n, 1, 1000000000, "a_i");
    inf.readEoln();

    for (int i = 1; i <= q; ++i) {
        setTestCase(i);
        int l = inf.readInt(1, n, "l");
        inf.readSpace();
        inf.readInt(l, n, "r");
        inf.readEoln();
    }

    inf.readEof();
}
