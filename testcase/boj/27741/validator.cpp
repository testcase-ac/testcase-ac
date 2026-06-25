#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 300, "N");
    inf.readSpace();
    int k = inf.readInt(1, n, "K");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            int cell = inf.readInt(0, 1, "maze_cell");
            if (j < n) {
                inf.readSpace();
            } else {
                inf.readEoln();
            }
            if (i == 1 && j == 1) {
                ensuref(cell == 0, "maze cell (1, 1) must be 0");
            }
        }
    }

    inf.readEof();
}
