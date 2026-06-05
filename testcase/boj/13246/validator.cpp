#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 5, "N");
    inf.readSpace();
    inf.readLong(1LL, 100000000000LL, "B");
    inf.readEoln();

    for (int row = 0; row < n; ++row) {
        inf.readInts(n, 0, 1000, "A_i_j");
        inf.readEoln();
    }

    inf.readEof();
}
