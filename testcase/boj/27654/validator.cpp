#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "N");
    inf.readSpace();
    int k = inf.readInt(1, n, "K");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        int p = inf.readInt(0, 100000, "P_i");
        inf.readSpace();
        int q = inf.readInt(1, 100000, "Q_i");
        inf.readEoln();
        ensuref(p <= q, "P_i must be at most Q_i at row %d: %d > %d", i, p, q);
    }

    inf.readEof();
}
