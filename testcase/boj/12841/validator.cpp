#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 100000, "n");
    inf.readEoln();

    inf.readInts(n, 1, 100000, "cross");
    inf.readEoln();

    inf.readInts(n - 1, 1, 100000, "left");
    inf.readEoln();

    inf.readInts(n - 1, 1, 100000, "right");
    inf.readEoln();

    inf.readEof();
}
