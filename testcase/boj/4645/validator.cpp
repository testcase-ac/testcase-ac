#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int datasets = 0;
    while (true) {
        int n = inf.readInt(0, 30, "n");
        if (n == 0) {
            inf.readEoln();
            break;
        }

        ++datasets;
        ensuref(datasets <= 100, "too many data sets: %d", datasets);

        int limit = 1 << n;
        inf.readSpace();
        int x1 = inf.readInt(0, limit, "x1");
        inf.readSpace();
        int x2 = inf.readInt(0, limit, "x2");
        inf.readSpace();
        int y = inf.readInt(0, limit, "y");
        inf.readEoln();

        ensuref(x1 < x2, "x1 must be less than x2, got x1=%d x2=%d", x1, x2);
        (void)y;
    }

    ensuref(datasets >= 1, "input must contain at least one data set");
    inf.readEof();
}
