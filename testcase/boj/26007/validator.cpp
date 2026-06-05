#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "N");
    inf.readSpace();
    int m = inf.readInt(1, 1000000, "M");
    inf.readSpace();
    inf.readInt(-1000000000, 1000000000, "K");
    inf.readSpace();
    inf.readInt(-10000, 10000, "X");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        if (i > 1) {
            inf.readSpace();
        }
        inf.readInt(-10000, 10000, "A_i");
    }
    inf.readEoln();

    for (int j = 1; j <= m; ++j) {
        int l = inf.readInt(1, n, "l_j");
        inf.readSpace();
        inf.readInt(l + 1, n + 1, "r_j");
        inf.readEoln();
    }

    inf.readEof();
}
