#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 500, "n");
    inf.readEoln();

    int a[500][500];
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int lower = (i == j ? 0 : 1);
            int upper = (i == j ? 0 : 1000000);
            a[i][j] = inf.readInt(lower, upper, "a_i_j");
            if (j + 1 == n) {
                inf.readEoln();
            } else {
                inf.readSpace();
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            ensuref(a[i][j] == a[j][i],
                    "matrix is not symmetric at (%d, %d): %d != %d",
                    i + 1, j + 1, a[i][j], a[j][i]);
        }
    }

    inf.readEof();
}
