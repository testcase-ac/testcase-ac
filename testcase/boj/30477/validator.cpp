#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000, "N");
    inf.readEoln();

    inf.readInts(3 * n, -100000, 100000, "B_i");
    inf.readEoln();
    inf.readEof();
}
