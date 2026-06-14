#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 200000, "n");
    inf.readSpace();
    int q = inf.readInt(1, 200000, "q");
    inf.readEoln();

    inf.readInts(n, 1, n, "A_i");
    inf.readEoln();

    int lastType = 0;
    for (int query = 1; query <= q; ++query) {
        int type = inf.readInt(1, 2, "query_type");
        inf.readSpace();

        if (type == 1) {
            inf.readInt(1, n, "i");
            inf.readSpace();
            inf.readInt(1, n, "x");
        } else {
            int l = inf.readInt(1, n, "l");
            inf.readSpace();
            int r = inf.readInt(l, n, "r");
        }
        inf.readEoln();
        lastType = type;
    }

    ensuref(lastType == 2, "the last query must be type 2");
    inf.readEof();
}
