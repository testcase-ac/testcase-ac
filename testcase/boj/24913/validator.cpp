#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "n");
    inf.readSpace();
    int q = inf.readInt(1, 300000, "q");
    inf.readEoln();

    for (int i = 1; i <= q; ++i) {
        int type = inf.readInt(1, 2, "type");
        inf.readSpace();
        int x = inf.readInt(0, 1000000, "x");
        inf.readSpace();

        if (type == 1) {
            int p = inf.readInt(1, n + 1, "p");
            (void)p;
        } else {
            int y = inf.readInt(0, 1000000, "y");
            (void)y;
        }
        inf.readEoln();

        if (i == q) {
            ensuref(type == 2, "last event must be a query");
        }
        (void)x;
    }

    inf.readEof();
}
