#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(0, 20, "n");
    inf.readSpace();
    int q = inf.readInt(1, 1000000, "q");
    inf.readEoln();

    int size = 1 << n;
    for (int i = 0; i < q; ++i) {
        int t = inf.readInt(0, 1, "t");
        inf.readSpace();
        inf.readInt(1, size, "x");
        inf.readEoln();
    }

    inf.readEof();
}
