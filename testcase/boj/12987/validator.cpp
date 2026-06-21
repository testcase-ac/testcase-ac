#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 50, "N");
    inf.readSpace();
    inf.readInt(1, 1000000000, "K");
    inf.readSpace();
    inf.readInt(1, 10000, "M");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        inf.readInts(n, -10000, 10000, "A_ij");
        inf.readEoln();
    }

    inf.readEof();
}
