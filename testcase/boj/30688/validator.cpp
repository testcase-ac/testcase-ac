#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 1000000, "N");
    inf.readSpace();
    int k = inf.readInt(2, n, "K");
    inf.readEoln();

    ensuref(k % 2 == 0, "K must be even, got %d", k);

    inf.readEof();
}
