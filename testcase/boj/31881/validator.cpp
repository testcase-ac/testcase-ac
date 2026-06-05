#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 200000, "n");
    inf.readSpace();
    int q = inf.readInt(1, 200000, "q");
    inf.readEoln();

    int reportCount = 0;
    for (int i = 1; i <= q; ++i) {
        int type = inf.readInt(1, 3, "type");
        if (type == 3) {
            ++reportCount;
            inf.readEoln();
            continue;
        }

        inf.readSpace();
        inf.readInt(1, n, "x");
        inf.readEoln();
    }

    ensuref(reportCount >= 1, "at least one type-3 query is required");
    inf.readEof();
}
