#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 300, "N");
    inf.readSpace();
    int m = inf.readInt(0, n * n, "M");
    inf.readSpace();
    int k = inf.readInt(0, n * n, "K");
    inf.readSpace();
    inf.readInt(1, 10000, "t");
    inf.readEoln();

    // CHECK: The statement bounds M and K by N^2 but does not explicitly say
    // mold or inspection coordinates are distinct, so duplicate coordinates are accepted.
    for (int i = 0; i < m; ++i) {
        inf.readInt(1, n, "M_x");
        inf.readSpace();
        inf.readInt(1, n, "M_y");
        inf.readEoln();
    }

    for (int i = 0; i < k; ++i) {
        inf.readInt(1, n, "K_x");
        inf.readSpace();
        inf.readInt(1, n, "K_y");
        inf.readEoln();
    }

    inf.readEof();
}
