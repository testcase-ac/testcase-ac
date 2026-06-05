#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 200000, "N");
    inf.readSpace();
    int q = inf.readInt(1, 200000, "Q");
    inf.readEoln();

    for (int i = 1; i <= q; ++i) {
        inf.readInt(1, n, "X_i");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
