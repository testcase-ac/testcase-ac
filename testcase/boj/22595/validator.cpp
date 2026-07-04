#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100, "n");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (j > 1) {
                inf.readSpace();
            }
            int cost = inf.readInt(0, 1000000, "c_i_j");
            if (i == j) {
                ensuref(cost == 0, "diagonal cost at (%d, %d) must be zero, found %d", i, j, cost);
            }
        }
        inf.readEoln();
    }

    inf.readEof();
}
