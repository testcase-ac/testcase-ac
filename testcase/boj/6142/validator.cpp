#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "N");
    inf.readSpace();
    int m = inf.readInt(1, 100000, "M");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        inf.readInt(1, 1000000000, "A_i");
        inf.readSpace();
        inf.readInt(1, 1000000000, "B_i");
        inf.readEoln();
    }

    for (int i = 1; i <= m; ++i) {
        inf.readInt(1, 1000000000, "C_i");
        inf.readSpace();
        inf.readInt(1, 1000000000, "D_i");
        inf.readEoln();
    }

    inf.readEof();
}
