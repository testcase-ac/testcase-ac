#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000, "N");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        int l = inf.readInt(1, 1000, "L_i");
        inf.readSpace();
        int r = inf.readInt(l, 1000, "R_i");
        inf.readEoln();
    }

    inf.readEof();
}
