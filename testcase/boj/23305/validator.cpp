#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000000, "n");
    inf.readEoln();

    inf.readInts(n, 1, 1000000, "A_i");
    inf.readEoln();

    inf.readInts(n, 1, 1000000, "B_i");
    inf.readEoln();

    inf.readEof();
}
