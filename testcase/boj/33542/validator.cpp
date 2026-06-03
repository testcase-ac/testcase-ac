#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(0, 100000000, "A");
    inf.readSpace();
    inf.readInt(0, 100000000, "B");
    inf.readEoln();

    int n = inf.readInt(1, 500000, "N");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        inf.readInt(0, 100000000, "L_i");
        inf.readSpace();
        inf.readInt(0, 100000000, "R_i");
        inf.readEoln();
    }

    inf.readEof();
}
