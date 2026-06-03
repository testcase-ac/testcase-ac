#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 200000, "n");
    inf.readSpace();
    int m = inf.readInt(1, 200000, "m");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        inf.readLong(-1000000000LL, 1000000000LL, "a_i");
        inf.readEoln();
    }

    for (int i = 0; i < m; ++i) {
        inf.readLong(-1000000000LL, 1000000000LL, "d_i");
        inf.readEoln();
    }

    inf.readEof();
}
