#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 300000, "N");
    inf.readSpace();
    inf.readInt(1, 1000000000, "D");
    inf.readEoln();

    inf.readInts(n, 1, 1000000000, "X_i");
    inf.readEoln();
    inf.readEof();
}
