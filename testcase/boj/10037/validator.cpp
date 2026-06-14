#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 50000, "N");
    inf.readSpace();
    int m = inf.readInt(1, 100000, "M");
    inf.readEoln();

    for (int i = 1; i <= m; ++i) {
        int a = inf.readInt(1, n, "A_i");
        inf.readSpace();
        int b = inf.readInt(1, n, "B_i");
        inf.readEoln();

        ensuref(a != b, "path %d connects pasture %d to itself", i, a);
    }

    inf.readEof();
}
