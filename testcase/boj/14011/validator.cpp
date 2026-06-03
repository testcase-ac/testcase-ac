#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000, "N");
    inf.readSpace();
    inf.readInt(0, 1000000, "M");
    inf.readEoln();

    inf.readInts(n, 0, 1000000, "A");
    inf.readEoln();

    inf.readInts(n, 0, 1000000, "B");
    inf.readEoln();

    inf.readEof();
}
