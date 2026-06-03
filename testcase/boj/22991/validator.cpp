#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 200000, "N");
    inf.readSpace();
    int m = inf.readInt(1, 200000, "M");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        inf.readLong(1LL, 1000000000LL, "a_i");
        inf.readSpace();
        inf.readLong(1LL, 1000000000LL, "b_i");
        inf.readEoln();
    }

    for (int j = 1; j <= m; ++j) {
        inf.readLong(1LL, 1000000000LL, "c_j");
        inf.readSpace();
        inf.readLong(1LL, 1000000000LL, "d_j");
        inf.readEoln();
    }

    inf.readEof();
}
