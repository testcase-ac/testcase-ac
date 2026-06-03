#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 3000, "N");
    inf.readSpace();
    int m = inf.readInt(1, 3000, "M");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        inf.readInt(1, 30000, "X_i");
        inf.readSpace();
        inf.readInt(1, 30000, "Y_i");
        inf.readEoln();
    }

    for (int i = 1; i <= m; ++i) {
        if (i > 1) {
            inf.readSpace();
        }
        inf.readInt(1, n, "P_i");
    }
    inf.readEoln();

    for (int i = 0; i <= m; ++i) {
        if (i > 0) {
            inf.readSpace();
        }
        inf.readInt(1, 30000, i == 0 ? "R_0" : "R_i");
    }
    inf.readEoln();

    inf.readEof();
}
