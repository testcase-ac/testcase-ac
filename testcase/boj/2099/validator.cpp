#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 200, "N");
    inf.readSpace();
    inf.readInt(1, 1000000, "K");
    inf.readSpace();
    int m = inf.readInt(1, 1000000, "M");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        int left = inf.readInt(1, n, "choice_left");
        inf.readSpace();
        int right = inf.readInt(1, n, "choice_right");
        inf.readEoln();

        ensuref(left != i, "person %d points to self with left hand", i);
        ensuref(right != i, "person %d points to self with right hand", i);
    }

    for (int i = 1; i <= m; ++i) {
        inf.readInt(1, n, "a");
        inf.readSpace();
        inf.readInt(1, n, "b");
        inf.readEoln();
    }

    inf.readEof();
}
