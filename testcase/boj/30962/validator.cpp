#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int q = inf.readInt(1, 100000, "Q");
    inf.readEoln();

    for (int i = 1; i <= q; ++i) {
        setTestCase(i);

        int x1 = inf.readInt(1, 100000, "x1");
        inf.readSpace();
        int y1 = inf.readInt(1, 100000, "y1");
        inf.readSpace();
        int x2 = inf.readInt(1, 100000, "x2");
        inf.readSpace();
        int y2 = inf.readInt(1, 100000, "y2");
        inf.readSpace();
        int w = inf.readInt(1, 100000, "w");
        inf.readEoln();

        long long cross = 1LL * x1 * y2 - 1LL * y1 * x2;
        ensuref(cross < 0,
                "query %d must place (x2, y2) clockwise from (x1, y1): "
                "(%d, %d), (%d, %d), cross=%lld",
                i, x1, y1, x2, y2, cross);
    }

    inf.readEof();
}
