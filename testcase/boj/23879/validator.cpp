#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: The statement only says N <= 100000; require at least one stall.
    int n = inf.readInt(1, 100000, "N");
    inf.readEoln();

    inf.readInts(n, 0, 10000, "p");
    inf.readEoln();

    inf.readInts(n, 0, 10000, "t");
    inf.readEoln();

    inf.readEof();
}
