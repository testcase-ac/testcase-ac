#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000, "N");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        if (i > 1) {
            inf.readSpace();
        }
        inf.readInt(1, 1000000000, "A_i");
    }
    inf.readEoln();

    int q = inf.readInt(1, 10000, "Q");
    inf.readEoln();

    bool hasTypeOneQuery = false;
    for (int i = 1; i <= q; ++i) {
        int type = inf.readInt(1, 2, "query_type");
        inf.readSpace();
        int l = inf.readInt(1, n, "l");
        inf.readSpace();
        int r = inf.readInt(l, n, "r");

        if (type == 1) {
            hasTypeOneQuery = true;
            inf.readSpace();
            inf.readInt(1, 1000000000, "k");
        }
        inf.readEoln();
    }

    ensuref(hasTypeOneQuery, "at least one type-1 query is required");
    inf.readEof();
}
