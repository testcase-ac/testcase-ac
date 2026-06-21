#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000000, "N");
    inf.readSpace();
    int m = inf.readInt(1, 1000000, "M");
    inf.readEoln();

    inf.readInts(n, 1, 20, "s_i");
    inf.readEoln();

    inf.readInts(m, 1, 20, "l_i");
    inf.readEoln();

    inf.readEof();
}
