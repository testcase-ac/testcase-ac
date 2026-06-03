#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000, "N");
    inf.readSpace();
    int m = inf.readInt(0, 1000, "M");
    inf.readEoln();

    for (int i = 1; i <= m; ++i) {
        int l = inf.readInt(1, n, "L_i");
        inf.readSpace();
        int r = inf.readInt(l, n, "R_i");
        inf.readSpace();
        inf.readInt(1, r - l + 1, "K_i");
        inf.readEoln();
    }

    inf.readEof();
}
