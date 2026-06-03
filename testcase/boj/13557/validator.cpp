#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "n");
    inf.readEoln();

    inf.readInts(n, -100000, 100000, "a");
    inf.readEoln();

    int m = inf.readInt(1, 100000, "m");
    inf.readEoln();

    for (int query = 1; query <= m; ++query) {
        int x1 = inf.readInt(1, n, "x1");
        inf.readSpace();
        int y1 = inf.readInt(1, n, "y1");
        inf.readSpace();
        int x2 = inf.readInt(1, n, "x2");
        inf.readSpace();
        int y2 = inf.readInt(1, n, "y2");
        inf.readEoln();

        ensuref(x1 <= x2, "query %d violates x1 <= x2: %d > %d", query, x1, x2);
        ensuref(y1 <= y2, "query %d violates y1 <= y2: %d > %d", query, y1, y2);
        ensuref(x1 <= y1, "query %d violates x1 <= y1: %d > %d", query, x1, y1);
        ensuref(x2 <= y2, "query %d violates x2 <= y2: %d > %d", query, x2, y2);
    }

    inf.readEof();
}
