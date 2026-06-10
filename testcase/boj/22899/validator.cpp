#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "N");
    inf.readSpace();
    int k = inf.readInt(1, n, "K");
    inf.readEoln();

    inf.readInts(n, 1, n, "a_i");
    inf.readEoln();

    inf.readLongs(n, 1LL, 1000000000LL, "b_i");
    inf.readEoln();

    inf.readEof();
}
