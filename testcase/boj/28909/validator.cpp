#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000, "n");
    inf.readSpace();
    int m = inf.readInt(1, 1000, "m");
    inf.readSpace();
    int k = inf.readInt(0, n, "k");
    inf.readEoln();

    inf.readInts(n, 1, 1000, "a_i");
    inf.readEoln();

    inf.readInts(m, 1, 1000, "b_j");
    inf.readEoln();

    inf.readEof();
}
