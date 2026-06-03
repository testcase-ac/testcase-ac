#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(5, 500000, "N");
    inf.readEoln();

    inf.readInts(n, 1, 1000000, "A_i");
    inf.readEoln();
    inf.readEof();
}
