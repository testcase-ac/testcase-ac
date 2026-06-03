#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 100000, "N");
    inf.readSpace();
    int m = inf.readInt(1, 100, "M");
    inf.readSpace();
    inf.readInt(1, n, "A");
    inf.readSpace();
    inf.readInt(1, n, "B");
    inf.readEoln();

    for (int i = 1; i <= m; ++i) {
        int l = inf.readInt(1, n - 1, "L_i");
        inf.readSpace();
        int r = inf.readInt(l, n - 1, "R_i");
        inf.readEoln();
    }

    inf.readEof();
}
