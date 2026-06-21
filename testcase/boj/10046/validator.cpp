#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int m = inf.readInt(1, 10000, "M");
    inf.readSpace();
    int n = inf.readInt(1, 500, "N");
    inf.readEoln();

    for (int i = 1; i <= m; ++i) {
        inf.readInt(1, 10000, "P_i");
        inf.readEoln();
    }

    for (int j = 1; j <= n; ++j) {
        inf.readInt(1, 10000, "C_j");
        inf.readSpace();
        inf.readInt(1, 10000, "E_j");
        inf.readEoln();
    }

    inf.readEof();
}
