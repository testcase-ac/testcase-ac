#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000, "N");
    inf.readSpace();
    int q = inf.readInt(1, 200000, "Q");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            inf.readInt(0, 100, "A_ij");
            if (j == n) {
                inf.readEoln();
            } else {
                inf.readSpace();
            }
        }
    }

    for (int i = 1; i <= q; ++i) {
        int r1 = inf.readInt(1, n, "R1");
        inf.readSpace();
        int c1 = inf.readInt(1, n, "C1");
        inf.readSpace();
        int r2 = inf.readInt(r1, n, "R2");
        inf.readSpace();
        int c2 = inf.readInt(c1, n, "C2");
        inf.readSpace();
        inf.readInt(0, 100, "V");
        inf.readEoln();
    }

    inf.readEof();
}
