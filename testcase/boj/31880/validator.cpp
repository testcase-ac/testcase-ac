#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 12, "N");
    inf.readSpace();
    int m = inf.readInt(1, 12, "M");
    inf.readEoln();

    inf.readInts(n, 0, 10, "a_i");
    inf.readEoln();

    inf.readInts(m, 0, 10, "b_i");
    inf.readEoln();

    inf.readEof();
}
