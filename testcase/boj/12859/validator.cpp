#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 300, "n");
    inf.readEoln();

    inf.readLongs(n, 1LL, 1000000000LL, "l_i");
    inf.readEoln();

    inf.readInts(n, 1, 100000, "c_i");
    inf.readEoln();

    inf.readEof();
}
