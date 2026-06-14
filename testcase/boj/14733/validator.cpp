#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 3000, "N");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        int x1 = inf.readInt(-50000, 50000, "x1");
        inf.readSpace();
        int y1 = inf.readInt(-50000, 50000, "y1");
        inf.readSpace();
        int x2 = inf.readInt(-50000, 50000, "x2");
        inf.readSpace();
        int y2 = inf.readInt(-50000, 50000, "y2");
        inf.readEoln();

        ensuref(x1 < x2,
                "rectangle %d must satisfy x1 < x2, got %d >= %d",
                i,
                x1,
                x2);
        ensuref(y1 < y2,
                "rectangle %d must satisfy y1 < y2, got %d >= %d",
                i,
                y1,
                y2);
    }

    inf.readEof();
}
