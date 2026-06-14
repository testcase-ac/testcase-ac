#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 50, "n");
    inf.readSpace();
    int m = inf.readInt(2, 50, "m");
    inf.readSpace();
    int t = inf.readInt(n + m - 1, 500, "t");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (j > 0) {
                inf.readSpace();
            }
            int w = inf.readInt(0, 100, "w_ij");
            if ((i == 0 && j == 0) || (i == n - 1 && j == m - 1)) {
                ensuref(w == 0, "w[%d][%d] must be 0 at home or school, got %d", i, j, w);
            }
        }
        inf.readEoln();
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (j > 0) {
                inf.readSpace();
            }
            inf.readInt(0, 100, "time_ij");
        }
        inf.readEoln();
    }

    inf.readEof();
}
