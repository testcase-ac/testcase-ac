#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100, "N");
    inf.readSpace();
    inf.readInt(1, 100000, "H");
    inf.readEoln();

    inf.readInts(n, 1, 100, "A_i");
    inf.readEoln();

    inf.readEof();
}
