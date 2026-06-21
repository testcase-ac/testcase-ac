#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000, "n");
    inf.readSpace();
    int m = inf.readInt(1, 1000, "m");
    inf.readSpace();
    int q = inf.readInt(1, 10000, "q");
    inf.readEoln();

    for (int i = 1; i <= q; ++i) {
        int x1 = inf.readInt(1, n, "x1");
        inf.readSpace();
        int y1 = inf.readInt(1, m, "y1");
        inf.readSpace();
        int x2 = inf.readInt(x1, n, "x2");
        inf.readSpace();
        int y2 = inf.readInt(y1, m, "y2");
        inf.readEoln();

        ensuref(x1 == x2 || y1 == y2,
                "stroke %d is not horizontal or vertical: (%d, %d) to (%d, %d)",
                i, x1, y1, x2, y2);
    }

    inf.readEof();
}
