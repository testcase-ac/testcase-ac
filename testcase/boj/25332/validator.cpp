#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 200000, "N");
    inf.readEoln();

    inf.readInts(n, 1, 10000, "A_i");
    inf.readEoln();

    inf.readInts(n, 1, 10000, "B_i");
    inf.readEoln();

    inf.readEof();
}
