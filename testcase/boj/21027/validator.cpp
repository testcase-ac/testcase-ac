#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 1000, "N");
    inf.readSpace();
    int k = inf.readInt(2, n, "K");
    inf.readEoln();

    inf.readInts(n, 0, 1000, "A_i");
    inf.readEoln();

    inf.readEof();
}
