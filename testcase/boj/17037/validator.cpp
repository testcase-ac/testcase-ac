#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "N");
    inf.readSpace();
    inf.readInt(1, n, "K");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        int x1 = inf.readInt(0, 1000, "x1");
        inf.readSpace();
        int y1 = inf.readInt(0, 1000, "y1");
        inf.readSpace();
        int x2 = inf.readInt(0, 1000, "x2");
        inf.readSpace();
        int y2 = inf.readInt(0, 1000, "y2");
        inf.readEoln();

        ensuref(x1 < x2, "rectangle %d must have positive width: x1=%d, x2=%d", i, x1, x2);
        ensuref(y1 < y2, "rectangle %d must have positive height: y1=%d, y2=%d", i, y1, y2);
    }

    inf.readEof();
}
