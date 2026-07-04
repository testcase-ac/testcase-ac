#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 50, "n");
    inf.readSpace();
    inf.readLong(1LL, 1000000000LL, "C");
    inf.readEoln();

    inf.readInts(n, 1, 1000000, "t");
    inf.readEoln();

    inf.readInts(n, 1, 1000000, "x");
    inf.readEoln();

    inf.readEof();
}
