#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "n");
    inf.readSpace();
    int m = inf.readInt(1, 100000, "m");
    inf.readEoln();

    inf.readInts(n, -10000, 10000, "h_i");
    inf.readEoln();

    for (int i = 0; i < m; ++i) {
        int a = inf.readInt(1, n, "a");
        inf.readSpace();
        inf.readInt(a, n, "b");
        inf.readSpace();
        inf.readInt(-100, 100, "k");
        inf.readEoln();
    }

    inf.readEof();
}
