#include "testlib.h"

#include <cstdlib>

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(4, 200000, "n");
    inf.readSpace();
    int q = inf.readInt(1, 200000, "q");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        if (i > 1) {
            inf.readSpace();
        }
        int a = inf.readInt(-10, 10, "a_i");
        ensuref(a != 0, "a_%d must be nonzero", i);
    }
    inf.readEoln();

    for (int i = 1; i <= q; ++i) {
        if (i > 1) {
            inf.readSpace();
        }
        inf.readInt(1, n, "q_i");
    }
    inf.readEoln();

    inf.readEof();
}
