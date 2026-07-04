#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(30000, 50000, "N");
    inf.readEoln();

    inf.readInts(n, 0, 10000, "A_i");
    inf.readEoln();

    inf.readEof();
}
