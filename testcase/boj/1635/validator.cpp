#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 100, "N");
    inf.readSpace();
    int m = inf.readInt(1, 10000, "M");
    inf.readEoln();

    ensuref(n % 2 == 0, "N must be even, got %d", n);

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            int value = inf.readInt(-1, 1, "a_i_j");
            ensuref(value == -1 || value == 1,
                    "a[%d][%d] must be -1 or 1, got %d", i + 1, j + 1, value);
            if (j + 1 < n) {
                inf.readSpace();
            }
        }
        inf.readEoln();
    }

    inf.readEof();
}
