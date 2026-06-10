#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 2000, "N");
    inf.readSpace();
    int m = inf.readInt(1, 2000, "M");
    inf.readSpace();
    int q = inf.readInt(1, 2000, "Q");
    inf.readEoln();

    for (int i = 1; i <= m; ++i) {
        int c = inf.readInt(1, n, "C_i");
        vector<bool> seen(n + 1, false);

        for (int j = 1; j <= c; ++j) {
            inf.readSpace();
            int p = inf.readInt(1, n, "P_i_j");
            ensuref(!seen[p], "duplicate input index at neuron %d: %d", i, p);
            seen[p] = true;
        }

        for (int j = 1; j <= c; ++j) {
            inf.readSpace();
            inf.readInt(1, 100, "W_i_j");
        }

        inf.readSpace();
        inf.readInt(1, 100, "B_i");
        inf.readEoln();
    }

    for (int i = 1; i <= m; ++i) {
        if (i > 1) {
            inf.readSpace();
        }
        inf.readInt(1, 100, "W_M_1_i");
    }
    inf.readSpace();
    inf.readInt(1, 100, "B_M_1");
    inf.readEoln();

    for (int i = 1; i <= q; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (j > 1) {
                inf.readSpace();
            }
            inf.readInt(1, 100, "A_i");
        }
        inf.readEoln();
    }

    inf.readEof();
}
