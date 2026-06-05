#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readLong(1LL, 1000000000LL, "N");
    inf.readSpace();
    int k = inf.readInt(1, 15, "K");
    inf.readEoln();

    inf.readInts(k, 1, 100, "A_i");
    inf.readEoln();

    inf.readEof();
}
