#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 20, "n");
    inf.readSpace();
    int m = inf.readInt(1, 20, "m");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        if (i > 0) {
            inf.readSpace();
        }
        inf.readToken("[a-z]{1,10}", "s_i");
    }
    inf.readEoln();

    for (int i = 0; i < m; ++i) {
        if (i > 0) {
            inf.readSpace();
        }
        inf.readToken("[a-z]{1,10}", "t_i");
    }
    inf.readEoln();

    int q = inf.readInt(1, 2020, "q");
    inf.readEoln();

    for (int i = 0; i < q; ++i) {
        inf.readInt(1, 1000000000, "y");
        inf.readEoln();
    }

    inf.readEof();
}
