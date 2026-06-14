#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 500000, "N");
    inf.readSpace();
    int m = inf.readInt(1, 500000, "M");
    inf.readEoln();

    inf.readInts(n, 1, 500000, "A_i");
    inf.readEoln();

    inf.readInts(n, 1, 500000, "B_i");
    inf.readEoln();

    inf.readEof();
}
