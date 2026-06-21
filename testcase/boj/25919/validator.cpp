#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 100, "N");
    inf.readSpace();
    int m = inf.readInt(2, 100, "M");
    inf.readEoln();

    int l = inf.readInt(2, 10000, "L");
    inf.readSpace();
    int e = inf.readInt(0, l - 1, "E");
    inf.readSpace();
    int k = inf.readInt(l, 10000, "K");
    inf.readEoln();

    int startCount = 0;
    int raidCount = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            int a = inf.readInt(-3, 10000, "A_i_j");
            ensuref(a == -3 || a == -2 || a == -1 || a == 0 || (1 <= a && a <= 10000),
                    "invalid cell value at (%d, %d): %d", i, j, a);

            if (a == -3) {
                ++startCount;
            } else if (a == -2) {
                ++raidCount;
            }

            if (j < m) {
                inf.readSpace();
            } else {
                inf.readEoln();
            }
        }
    }

    ensuref(startCount == 1, "expected exactly one start cell, found %d", startCount);
    ensuref(raidCount == 1, "expected exactly one raid cell, found %d", raidCount);

    inf.readEof();
}
