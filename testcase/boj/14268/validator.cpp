#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 100000, "n");
    inf.readSpace();
    int m = inf.readInt(2, 100000, "m");
    inf.readEoln();

    int president = inf.readInt(-1, -1, "parent_1");
    (void)president;
    for (int i = 2; i <= n; ++i) {
        inf.readSpace();
        int parent = inf.readInt(1, i - 1, "parent_i");
        ensuref(parent < i, "parent of employee %d must be less than %d", i, i);
    }
    inf.readEoln();

    for (int q = 1; q <= m; ++q) {
        int type = inf.readInt(1, 2, "type");
        inf.readSpace();
        if (type == 1) {
            inf.readInt(2, n, "i");
            inf.readSpace();
            inf.readInt(1, 1000, "w");
        } else {
            inf.readInt(1, n, "i");
        }
        inf.readEoln();
    }

    inf.readEof();
}
