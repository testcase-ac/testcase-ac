#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 1000, "N");
    inf.readSpace();
    int m = inf.readInt(2, 1000, "M");
    inf.readEoln();

    int hx = inf.readInt(1, n, "Hx");
    inf.readSpace();
    int hy = inf.readInt(1, m, "Hy");
    inf.readEoln();

    int ex = inf.readInt(1, n, "Ex");
    inf.readSpace();
    int ey = inf.readInt(1, m, "Ey");
    inf.readEoln();

    ensuref(hx != ex || hy != ey, "start and exit positions must be distinct");

    // CHECK: The statement gives only a binary maze and does not state that
    // the start or exit cell is necessarily empty, so both 0 and 1 are accepted.
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (j > 1) {
                inf.readSpace();
            }
            inf.readInt(0, 1, "maze_cell");
        }
        inf.readEoln();
    }

    inf.readEof();
}
