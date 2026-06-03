#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100, "N");
    inf.readEoln();

    int a = inf.readInt(0, n, "A");
    inf.readSpace();
    int b = inf.readInt(0, n, "B");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        int p = inf.readInt(1, 100, "p_i");
        inf.readSpace();
        int q = inf.readInt(1, 100, "q_i");
        inf.readSpace();
        int r = inf.readInt(1, 100, "r_i");
        inf.readSpace();
        int s = inf.readInt(1, 100, "s_i");
        inf.readEoln();

        ensuref(p <= r, "expected p_%d <= r_%d, got %d > %d", i, i, p, r);
        ensuref(q <= r, "expected q_%d <= r_%d, got %d > %d", i, i, q, r);
        ensuref(r <= s, "expected r_%d <= s_%d, got %d > %d", i, i, r, s);
    }

    inf.readEof();
}
