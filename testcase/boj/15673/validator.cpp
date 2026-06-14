#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 100000, "N");
    inf.readEoln();

    inf.readInts(n, -100, 100, "P_i");
    inf.readEoln();

    inf.readEof();
}
