#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 300, "N");
    inf.readSpace();
    inf.readInt(2, 1000000000, "X");
    inf.readEoln();

    inf.readInts(n, 1, 1000000000, "A");
    inf.readEoln();
    inf.readEof();
}
