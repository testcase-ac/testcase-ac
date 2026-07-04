#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 20000, "n");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        int l = inf.readInt(1, n, "L_i");
        inf.readSpace();
        int r = inf.readInt(l, n, "R_i");
        inf.readEoln();
    }

    inf.readEof();
}
