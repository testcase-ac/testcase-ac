#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 2000, "N");
    inf.readSpace();
    int m = inf.readInt(1, 2000, "M");
    inf.readSpace();
    int k = inf.readInt(1, 2000, "K");
    inf.readEoln();

    ensuref(n > m * (k - 1), "N problems must be unreachable before K days");

    inf.readEof();
}
