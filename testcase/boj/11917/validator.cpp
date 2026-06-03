#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 50000, "N");
    inf.readEoln();

    inf.readInts(n, -1000000, 1000000, "S_i");
    inf.readEoln();

    inf.readInt(1, 1000000000, "M");
    inf.readEoln();
    inf.readEof();
}
