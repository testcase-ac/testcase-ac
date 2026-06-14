#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 5000, "N");
    inf.readEoln();

    inf.readInts(n, 0, 1000000, "E_i");
    inf.readEoln();

    inf.readInts(n, 0, 1000000, "C_i");
    inf.readEoln();

    inf.readEof();
}
