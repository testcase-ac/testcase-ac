#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 10000, "n");
    inf.readSpace();
    int r = inf.readInt(1, 2, "r");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        int x1 = inf.readInt(0, 10000, "x1");
        inf.readSpace();
        int y1 = inf.readInt(0, 10000, "y1");
        inf.readSpace();
        int x2 = inf.readInt(0, 10000, "x2");
        inf.readSpace();
        int y2 = inf.readInt(0, 10000, "y2");
        inf.readEoln();

        ensuref(x1 < x2, "rectangle %d must have positive width: x1=%d, x2=%d", i, x1, x2);
        ensuref(y1 < y2, "rectangle %d must have positive height: y1=%d, y2=%d", i, y1, y2);
    }

    inf.readEof();
}
