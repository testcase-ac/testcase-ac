#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "N");
    inf.readSpace();
    int m = inf.readInt(1, 100000, "M");
    inf.readEoln();

    inf.readInts(n, 1, 100000000, "b_i");
    inf.readEoln();

    inf.readInts(m, 1, 100000000, "f_i");
    inf.readEoln();

    inf.readEof();
    return 0;
}
