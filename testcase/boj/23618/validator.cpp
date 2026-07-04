#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 2000, "N");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (j > 1) {
                inf.readSpace();
            }

            int g = inf.readInt(0, 9999, "g_i_j");
            if (i == j) {
                ensuref(g == 0, "main diagonal must be zero at (%d, %d), found %d", i, j, g);
            }
        }
        inf.readEoln();
    }

    inf.readEof();
}
