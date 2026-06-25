#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 100000, "N");
    inf.readSpace();
    int m = inf.readInt(2, 100000, "M");
    inf.readEoln();

    ensuref(1LL * n * m <= 100000LL, "N*M must be at most 100000, got %lld",
            1LL * n * m);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (j > 0) {
                inf.readSpace();
            }
            inf.readInt(1, 9, "A_i_j");
        }
        inf.readEoln();
    }

    inf.readEof();
}
