#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 300000, "n");
    inf.readEoln();
    inf.readInts(n, 1, n, "a_i");
    inf.readEoln();
    inf.readEof();
}
