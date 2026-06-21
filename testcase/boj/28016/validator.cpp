#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(3, 100, "N");
    inf.readSpace();
    int m = inf.readInt(3, 100, "M");
    inf.readEoln();

    int startCount = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            int cell = inf.readInt(0, 2, "board_cell");
            if (j + 1 < m) {
                inf.readSpace();
            } else {
                inf.readEoln();
            }

            ensuref(!(cell == 1 && (j == 0 || j == m - 1)),
                    "nail on border column at row %d column %d", i, j);
            if (cell == 2) {
                ensuref(i == 0, "initial ball position is not on top row: row %d column %d", i, j);
                ++startCount;
            }
        }
    }

    ensuref(startCount == 1, "expected exactly one initial ball position, found %d", startCount);
    inf.readEof();
}
