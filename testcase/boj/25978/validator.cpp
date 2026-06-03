#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000, "n");
    inf.readSpace();
    int m = inf.readInt(1, 300000, "m");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (j > 0) {
                inf.readSpace();
            }
            inf.readInt(1, 1000000, "a_ij");
        }
        inf.readEoln();
    }

    bool seenType2 = false;
    int type2Count = 0;
    for (int query = 1; query <= m; ++query) {
        int type = inf.readInt(1, 2, "type");
        inf.readSpace();
        int i1 = inf.readInt(0, n - 1, "i1");
        inf.readSpace();
        int j1 = inf.readInt(0, n - 1, "j1");
        inf.readSpace();
        int i2 = inf.readInt(i1, n - 1, "i2");
        inf.readSpace();
        int j2 = inf.readInt(j1, n - 1, "j2");

        if (type == 1) {
            ensuref(!seenType2, "type 1 query appears after a type 2 query at query %d", query);
            inf.readSpace();
            inf.readInt(1, 10000, "k");
        } else {
            seenType2 = true;
            ++type2Count;
        }
        inf.readEoln();
    }

    ensuref(type2Count >= 1, "at least one type 2 query is required");
    inf.readEof();
}
