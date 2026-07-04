#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 200000, "N");
    inf.readEoln();

    for (int i = 0; i <= n; ++i) {
        if (i > 0) {
            inf.readSpace();
        }
        inf.readInt(-100000, 100000, "A_i");
    }
    inf.readEoln();

    int m = inf.readInt(1, 200000, "M");
    inf.readEoln();

    bool hasType2Query = false;
    for (int q = 1; q <= m; ++q) {
        int type = inf.readInt(1, 2, "query_type");
        inf.readSpace();

        if (type == 1) {
            inf.readInt(0, n, "i");
            inf.readSpace();
            inf.readInt(-100000, 100000, "v");
        } else {
            hasType2Query = true;
            int a = inf.readInt(0, n, "a");
            inf.readSpace();
            int b = inf.readInt(a, n, "b");
        }
        inf.readEoln();
    }

    ensuref(hasType2Query, "at least one type 2 query is required");
    inf.readEof();
}
