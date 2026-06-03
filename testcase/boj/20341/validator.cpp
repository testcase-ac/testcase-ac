#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000, "n");
    inf.readEoln();

    inf.readInts(n, 0, 1000000, "k_i");
    inf.readEoln();
    inf.readInts(n, 0, 1000000, "a_i");
    inf.readEoln();
    inf.readInts(n, 0, 1000000, "b_i");
    inf.readEoln();

    inf.readEof();
}
