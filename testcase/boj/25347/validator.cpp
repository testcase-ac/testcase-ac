#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000000, "n");
    inf.readSpace();
    int x = inf.readInt(1, 1000000000, "x");
    inf.readSpace();
    int y = inf.readInt(x, 1000000000, "y");
    inf.readEoln();

    inf.readInts(n, 1, 1000000000, "r_i");
    inf.readEoln();

    inf.readInts(n, 1, 1000000000, "b_i");
    inf.readEoln();

    inf.readEof();
}
