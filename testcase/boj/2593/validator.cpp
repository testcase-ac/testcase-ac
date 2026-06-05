#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "N");
    inf.readSpace();
    int m = inf.readInt(1, 100, "M");
    inf.readEoln();

    for (int i = 1; i <= m; ++i) {
        inf.readInt(1, n, "X_i");
        inf.readSpace();
        inf.readInt(1, n, "Y_i");
        inf.readEoln();
    }

    int a = inf.readInt(1, n, "A");
    inf.readSpace();
    int b = inf.readInt(1, n, "B");
    inf.readEoln();
    ensuref(a != b, "A and B must be different: %d", a);

    inf.readEof();
}
