#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 3402, "N");
    inf.readSpace();
    inf.readInt(1, 12880, "M");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        inf.readInt(1, 400, "W_i");
        inf.readSpace();
        inf.readInt(1, 100, "D_i");
        inf.readEoln();
    }

    inf.readEof();
}
