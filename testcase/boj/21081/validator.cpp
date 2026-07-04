#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 50000, "n");
    inf.readEoln();

    inf.readInts(n, 1, 1000, "R_i");
    inf.readEoln();
    inf.readEof();
}
