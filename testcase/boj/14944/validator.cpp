#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 10000, "n");
    inf.readSpace();
    int m = inf.readInt(1, 10000, "m");
    inf.readEoln();

    inf.readInts(n, 1, 100, "L_i");
    inf.readEoln();

    for (int j = 1; j <= m; ++j) {
        int a = inf.readInt(1, n, "A_j");
        inf.readSpace();
        int b = inf.readInt(1, n, "B_j");
        inf.readSpace();
        inf.readInt(1, 100, "C_j");
        inf.readEoln();

        ensuref(a != b, "road %d connects house %d to itself", j, a);
    }

    inf.readEof();
    return 0;
}
