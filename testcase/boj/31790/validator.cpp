#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int maxN = 500000;

    int n = inf.readInt(1, maxN, "N");
    inf.readSpace();
    inf.readInt(1, maxN, "p");
    inf.readEoln();

    inf.readInts(n, 1, n, "b_i");
    inf.readEoln();

    inf.readEof();
}
