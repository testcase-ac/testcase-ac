#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 400, "N");
    inf.readSpace();
    int m = inf.readInt(1, 400, "M");
    inf.readEoln();

    inf.readInts(n, 1, 300, "G_i");
    inf.readEoln();

    inf.readInts(m, 1, 300, "B_i");
    inf.readEoln();

    inf.readInts(n, 1, 300, "L_i");
    inf.readEoln();

    inf.readInts(m, 1, 300, "U_i");
    inf.readEoln();

    inf.readEof();
}
