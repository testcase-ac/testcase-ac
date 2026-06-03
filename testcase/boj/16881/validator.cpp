#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int maxCells = 4999999;

    // CHECK: The statement gives no upper bounds for N or M; cap total matrix
    // cells below 5,000,000 scalar tokens per local validator policy.
    int n = inf.readInt(1, maxCells, "N");
    inf.readSpace();
    int m = inf.readInt(1, maxCells, "M");
    inf.readEoln();

    ensuref(1LL * n * m <= maxCells, "N*M must be at most %d", maxCells);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            inf.readInt(1, 1000, "a_ij");
            if (j + 1 == m) {
                inf.readEoln();
            } else {
                inf.readSpace();
            }
        }
    }

    inf.readEof();
}
