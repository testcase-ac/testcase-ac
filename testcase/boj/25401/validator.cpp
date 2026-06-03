#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 500, "N");
    inf.readEoln();

    inf.readInts(n, -1000000, 1000000, "x_i");
    inf.readEoln();
    inf.readEof();
}
