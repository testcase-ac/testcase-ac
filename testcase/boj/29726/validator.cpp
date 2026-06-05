#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 200000, "N");
    inf.readSpace();
    int m = inf.readInt(0, n - 2, "M");
    inf.readEoln();

    inf.readInts(n, 1, 100000, "A_i");
    inf.readEoln();

    inf.readEof();
}
