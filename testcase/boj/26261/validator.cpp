#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 200000, "N");
    inf.readSpace();
    int x = inf.readInt(2, 199999, "X");
    inf.readSpace();
    int k = inf.readInt(1, 199998, "K");
    inf.readEoln();

    ensuref(k < x, "expected K < X, got K=%d and X=%d", k, x);
    ensuref(x < n, "expected X < N, got X=%d and N=%d", x, n);

    for (int i = 0; i < n; ++i) {
        inf.readInt(0, 1, "A_i");
        if (i + 1 == n) {
            inf.readEoln();
        } else {
            inf.readSpace();
        }
    }

    inf.readEof();
}
