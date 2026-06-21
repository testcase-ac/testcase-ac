#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "n");
    inf.readSpace();
    int q = inf.readInt(1, 100000, "q");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        if (i > 1) {
            inf.readSpace();
        }
        inf.readInt(1, 100, "k_i");
    }
    inf.readEoln();

    int queryCount = 0;
    for (int i = 1; i <= q; ++i) {
        int t = inf.readInt(1, 2, "t_i");
        inf.readSpace();
        int a = inf.readInt(1, n, "a_i");
        inf.readSpace();
        if (t == 1) {
            inf.readInt(a, n, "b_i");
            ++queryCount;
        } else {
            inf.readInt(1, 100, "b_i");
        }
        inf.readEoln();
    }

    ensuref(queryCount >= 1, "at least one operation must have t_i = 1");
    inf.readEof();
}
