#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "N");
    inf.readEoln();

    inf.readInts(n, 1, 10000, "a_i");
    inf.readEoln();

    inf.readEof();
}
