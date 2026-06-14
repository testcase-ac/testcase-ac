#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(3, 2000, "N");
    inf.readSpace();
    inf.readInt(1, 1000000, "K");
    inf.readEoln();

    inf.readInts(n, 1, 100000000, "A_i");
    inf.readEoln();

    inf.readEof();
}
