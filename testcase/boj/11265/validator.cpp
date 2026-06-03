#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(5, 500, "N");
    inf.readSpace();
    int m = inf.readInt(1, 10000, "M");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            // CHECK: The statement gives T >= 1 for direct roads, but the official sample
            // uses 0 on every diagonal entry to represent travel from a room to itself.
            int low = (i == j ? 0 : 1);
            inf.readInt(low, 1000000, "T_ij");
            if (j < n) {
                inf.readSpace();
            } else {
                inf.readEoln();
            }
        }
    }

    for (int i = 1; i <= m; ++i) {
        inf.readInt(1, n, "A");
        inf.readSpace();
        inf.readInt(1, n, "B");
        inf.readSpace();
        inf.readInt(1, 1000000000, "C");
        inf.readEoln();
    }

    inf.readEof();
}
