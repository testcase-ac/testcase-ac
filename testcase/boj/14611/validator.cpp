#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 300, "n");
    inf.readSpace();
    int m = inf.readInt(2, 300, "m");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            long long cell = inf.readLong(-2LL, 1000000000LL, "cell");
            ensuref(cell >= 0 || cell == -1 || cell == -2,
                    "cell (%d, %d) has invalid value %lld", i, j, cell);
            if ((i == 1 && j == 1) || (i == n && j == m)) {
                ensuref(cell == -1, "endpoint (%d, %d) must be -1, found %lld", i, j, cell);
            }

            if (j == m) {
                inf.readEoln();
            } else {
                inf.readSpace();
            }
        }
    }

    inf.readEof();
}
