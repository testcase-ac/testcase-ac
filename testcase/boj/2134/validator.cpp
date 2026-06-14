#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 10000, "n");
    inf.readSpace();
    int m = inf.readInt(1, 10000, "m");
    inf.readSpace();
    int k = inf.readInt(1, 10000, "k");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        inf.readInt(0, 10000, "old_floor_count");
        inf.readEoln();
    }

    for (int i = 1; i <= m; ++i) {
        inf.readInt(0, 10000, "new_floor_capacity");
        inf.readEoln();
    }

    inf.readEof();
}
