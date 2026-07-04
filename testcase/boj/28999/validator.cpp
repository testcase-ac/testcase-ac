#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "n");
    inf.readSpace();
    int q = inf.readInt(1, 100000, "q");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        if (i > 1) {
            inf.readSpace();
        }
        inf.readInt(1, 100000000, "a_i");
    }
    inf.readEoln();

    for (int i = 1; i <= q; ++i) {
        int l = inf.readInt(1, n, "l");
        inf.readSpace();
        inf.readInt(l, n, "r");
        inf.readEoln();
    }

    inf.readEof();
}
