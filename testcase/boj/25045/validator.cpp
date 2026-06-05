#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 200000, "n");
    inf.readSpace();
    int m = inf.readInt(1, 200000, "m");
    inf.readEoln();

    inf.readInts(n, 0, 1000000000, "a");
    inf.readEoln();

    inf.readInts(m, 0, 1000000000, "b");
    inf.readEoln();

    inf.readEof();
}
