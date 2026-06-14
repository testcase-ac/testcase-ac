#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int k = inf.readInt(1, 50000, "K");
    inf.readSpace();
    int n = inf.readInt(1, 20000, "N");
    inf.readSpace();
    int c = inf.readInt(1, 100, "C");
    inf.readEoln();

    for (int i = 1; i <= k; ++i) {
        int s = inf.readInt(1, n, "S_i");
        inf.readSpace();
        int e = inf.readInt(1, n, "E_i");
        inf.readSpace();
        int m = inf.readInt(1, n, "M_i");
        inf.readEoln();

        ensuref(s < e, "group %d must travel forward: S_i=%d, E_i=%d", i, s, e);
        (void)m;
    }

    inf.readEof();
}
