#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int m = inf.readInt(1, 30, "M");
    inf.readSpace();
    int n = inf.readInt(1, 30, "N");
    inf.readEoln();

    int start_count = 0;
    int target_count = 0;
    for (int row = 1; row <= m; ++row) {
        for (int col = 1; col <= n; ++col) {
            int cell = inf.readInt(0, 4, "cell");
            if (cell == 3) {
                ++start_count;
            } else if (cell == 4) {
                ++target_count;
            }

            if (col < n) {
                inf.readSpace();
            } else {
                inf.readEoln();
            }
        }
    }

    ensuref(start_count == 1, "expected exactly one start cell, found %d", start_count);
    ensuref(target_count == 1, "expected exactly one target cell, found %d", target_count);

    inf.readEof();
}
