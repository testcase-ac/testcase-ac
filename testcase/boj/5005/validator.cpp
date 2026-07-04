#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int w = inf.readInt(1, 100, "W");
    inf.readSpace();
    int n = inf.readInt(1, 100, "N");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        int x1 = inf.readInt(-10000, 10000, "x1");
        inf.readSpace();
        int y1 = inf.readInt(-10000, 10000, "y1");
        inf.readSpace();
        int x2 = inf.readInt(-10000, 10000, "x2");
        inf.readSpace();
        int y2 = inf.readInt(-10000, 10000, "y2");
        inf.readEoln();

        ensuref(x1 != x2 || y1 != y2,
                "line %d uses the same point twice: (%d, %d)",
                i, x1, y1);
    }

    inf.readEof();
}
