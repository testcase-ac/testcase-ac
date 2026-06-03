#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 20, "N");
    inf.readSpace();
    inf.readInt(1, 100000, "K");
    inf.readEoln();

    inf.readInts(n, 1, 100000, "A_i");
    inf.readEoln();

    inf.readInts(n, 1, 100000, "P_i");
    inf.readEoln();

    inf.readEof();
}
