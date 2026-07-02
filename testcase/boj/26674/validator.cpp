#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000000, "n");
    inf.readSpace();
    int m = inf.readInt(1, 1000000, "m");
    inf.readEoln();

    for (int i = 1; i <= m; ++i) {
        int l = inf.readInt(1, n, "l_i");
        inf.readSpace();
        int r = inf.readInt(l, n, "r_i");
        inf.readSpace();
        inf.readInt(1, 3, "k_i");
        inf.readEoln();
    }

    inf.readEof();
}
