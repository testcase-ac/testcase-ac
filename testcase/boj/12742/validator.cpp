#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 200, "N");
    inf.readSpace();
    inf.readInt(1, 1000000, "X");
    inf.readSpace();
    inf.readInt(1, 1000000, "Y");
    inf.readEoln();

    inf.readInts(n, 1, 1000000, "GA_i");
    inf.readEoln();

    inf.readInts(n, 1, 1000000, "GB_i");
    inf.readEoln();

    inf.readInts(n, 1, 1000000, "W_i");
    inf.readEoln();

    inf.readEof();
}
