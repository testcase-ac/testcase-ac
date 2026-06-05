#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 300000, "N");
    inf.readSpace();
    int m = inf.readInt(1, 300000, "M");
    inf.readEoln();

    inf.readLongs(m, 1LL, 1000000000LL, "A_j");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        inf.readLong(1LL, 1000000000000LL, "B_i");
        inf.readEoln();
    }

    inf.readEof();
}
