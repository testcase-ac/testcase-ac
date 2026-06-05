#include "testlib.h"

#include <cstdlib>

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000, "n");
    inf.readSpace();
    int m = inf.readInt(1, 1000, "m");
    inf.readSpace();
    int q = inf.readInt(1, 200000, "Q");
    inf.readEoln();

    for (int i = 1; i <= q; ++i) {
        int type = inf.readInt(1, 3, "type");

        if (type == 1) {
            inf.readSpace();
            int dy = inf.readInt(-1, 1, "d_y");
            inf.readSpace();
            int dx = inf.readInt(-1, 1, "d_x");
            inf.readSpace();
            int y = inf.readInt(1, n, "y");
            inf.readSpace();
            int x = inf.readInt(1, m, "x");
            ensuref(std::abs(dy) + std::abs(dx) == 1,
                    "query %d has non-unit direction (%d, %d)", i, dy, dx);
        } else if (type == 2) {
            inf.readSpace();
            int y = inf.readInt(1, n, "y");
            inf.readSpace();
            int x = inf.readInt(1, m, "x");
            (void)y;
            (void)x;
        }

        inf.readEoln();
    }

    inf.readEof();
}
