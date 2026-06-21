#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 300000, "N");
    inf.readEoln();

    inf.readInts(n, 1, 300000, "A_i");
    inf.readEoln();

    int m = inf.readInt(1, 500000, "M");
    inf.readEoln();

    bool hasTypeTwo = false;
    for (int i = 1; i <= m; ++i) {
        int type = inf.readInt(1, 2, "query_type");
        inf.readSpace();

        if (type == 1) {
            inf.readInt(1, 300000, "x");
            inf.readSpace();
            inf.readInt(1, 300000, "y");
        } else {
            inf.readInt(1, n, "z");
            hasTypeTwo = true;
        }
        inf.readEoln();
    }

    ensuref(hasTypeTwo, "at least one type-2 query is required");
    inf.readEof();
}
