#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "N");
    inf.readSpace();
    int m = inf.readInt(0, 200000, "M");
    inf.readEoln();

    for (int i = 1; i <= m; ++i) {
        int x = inf.readInt(1, n, "x");
        inf.readSpace();
        int y = inf.readInt(1, n, "y");
        inf.readEoln();

        ensuref(x < y, "edge %d must satisfy x < y, got %d %d", i, x, y);
        // CHECK: the statement does not forbid repeated transitions, so duplicates are accepted.
    }

    inf.readEof();
}
