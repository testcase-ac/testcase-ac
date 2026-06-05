#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "N");
    inf.readEoln();

    inf.readInts(n, 1, n, "a_i");
    inf.readEoln();

    int q = inf.readInt(1, 100000, "Q");
    inf.readEoln();

    inf.readInts(q, 1, n, "s_i");
    inf.readEoln();

    inf.readEof();
}
