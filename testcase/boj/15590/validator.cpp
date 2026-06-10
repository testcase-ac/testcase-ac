#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "n");
    inf.readSpace();
    int m = inf.readInt(1, 100000, "m");
    inf.readSpace();
    int r = inf.readInt(1, 100000, "r");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        inf.readInt(1, 1000000, "c_i");
        inf.readEoln();
    }

    for (int i = 1; i <= m; ++i) {
        inf.readInt(1, 1000000, "q_i");
        inf.readSpace();
        inf.readInt(1, 1000000, "p_i");
        inf.readEoln();
    }

    for (int i = 1; i <= r; ++i) {
        inf.readInt(1, 1000000, "r_i");
        inf.readEoln();
    }

    inf.readEof();
}
