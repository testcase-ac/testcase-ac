#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 100000, "n");
    inf.readSpace();
    int m = inf.readInt(2, 100000, "m");
    inf.readEoln();

    int root_parent = inf.readInt(-1, -1, "parent_1");
    (void)root_parent;
    for (int i = 2; i <= n; ++i) {
        inf.readSpace();
        inf.readInt(1, i - 1, "parent_i");
    }
    inf.readEoln();

    for (int q = 1; q <= m; ++q) {
        int type = inf.readInt(1, 3, "query_type");
        if (type == 1) {
            inf.readSpace();
            inf.readInt(1, n, "i");
            inf.readSpace();
            inf.readInt(1, 1000, "w");
        } else if (type == 2) {
            inf.readSpace();
            inf.readInt(1, n, "i");
        }
        inf.readEoln();
    }

    inf.readEof();
}
