#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 2000, "N");
    inf.readSpace();
    int m = inf.readInt(1, 2000, "M");
    inf.readSpace();
    inf.readInt(0, 4000, "K");
    inf.readEoln();

    int startCount = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (j > 0) {
                inf.readSpace();
            }
            int cell = inf.readInt(0, 4, "cell");
            if (cell == 4) {
                ++startCount;
            }
        }
        inf.readEoln();
    }

    ensuref(startCount == 1, "expected exactly one start cell, found %d", startCount);
    inf.readEof();
}
