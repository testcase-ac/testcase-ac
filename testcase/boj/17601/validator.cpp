#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 1000, "n");
    inf.readSpace();
    int k = inf.readInt(2, n, "k");
    inf.readEoln();

    ensuref(n % 2 == 0, "n must be even, found %d", n);

    inf.readInts(n, 1, k, "v_i");
    inf.readEoln();
    inf.readEof();
}
