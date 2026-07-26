#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 3000, "N");
    inf.readSpace();
    inf.readInt(1, n - 1, "K1");
    inf.readSpace();
    inf.readInt(1, n - 1, "K2");
    inf.readEoln();

    inf.readInts(n, 1, 2, "S_i");
    inf.readEoln();
    inf.readEof();
}
