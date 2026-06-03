#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 13, "n");
    inf.readSpace();
    int m = inf.readInt(1, 10, "m");
    inf.readSpace();
    // CHECK: the constraint text says c > 1, but official sample 4 uses c = 1.
    int c = inf.readInt(1, 20, "c");
    inf.readEoln();

    inf.readInts(n, 1, 20, "w");
    inf.readEoln();
    inf.readEof();
}
