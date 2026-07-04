#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 200000, "n");
    inf.readSpace();
    int q = inf.readInt(1, 200000, "q");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        if (i > 1) {
            inf.readSpace();
        }
        inf.readInt(1, 1000000, "a_i");
    }
    inf.readEoln();

    bool hasQuery = false;
    for (int i = 1; i <= q; ++i) {
        int type = inf.readInt(1, 2, "type");
        inf.readSpace();
        int l = inf.readInt(1, n, "l");
        inf.readSpace();
        int r = inf.readInt(l, n, "r");

        if (type == 1) {
            inf.readSpace();
            inf.readInt(1, 1000000, "v");
        } else {
            hasQuery = true;
        }
        inf.readEoln();
    }

    ensuref(hasQuery, "at least one operation must be of type 2");
    inf.readEof();
}
