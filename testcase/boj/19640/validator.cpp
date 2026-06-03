#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "N");
    inf.readSpace();
    int m = inf.readInt(2, 100000, "M");
    inf.readSpace();
    int k = inf.readInt(0, n - 1, "K");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        inf.readInt(0, 36500, "D_i");
        inf.readSpace();
        inf.readInt(0, 100000000, "H_i");
        inf.readEoln();
    }

    inf.readEof();
}
