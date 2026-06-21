#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 200000, "n");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        inf.readLong(1LL, 1000000000LL, "a_i");
        inf.readSpace();
        int l = inf.readInt(1, n, "l_i");
        inf.readSpace();
        inf.readInt(l, n, "r_i");
        inf.readEoln();
    }

    inf.readEof();
}
