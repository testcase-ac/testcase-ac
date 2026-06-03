#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 1000, "N");
    inf.readSpace();
    int m = inf.readInt(2, 1000, "M");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (j > 1) {
                inf.readSpace();
            }
            inf.readInt(-1000, 1000, "a_i_j");
        }
        inf.readEoln();
    }

    int x1 = inf.readInt(0, n, "x1");
    inf.readSpace();
    int y1 = inf.readInt(0, m, "y1");
    inf.readSpace();
    int x2 = inf.readInt(0, n, "x2");
    inf.readSpace();
    int y2 = inf.readInt(0, m, "y2");
    inf.readEoln();

    ensuref(x1 == x2 || y1 == y2,
            "wall must be axis-aligned: (%d, %d) to (%d, %d)",
            x1,
            y1,
            x2,
            y2);

    inf.readEof();
}
