#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100, "N");
    inf.readSpace();
    int k = inf.readInt(1, 10, "K");
    inf.readEoln();

    ensuref(k <= n, "K must not exceed N: K=%d, N=%d", k, n);

    inf.readInts(n, 0, 1, "current_i");
    inf.readEoln();

    inf.readInts(n, 0, 1, "target_i");
    inf.readEoln();

    inf.readEof();
}
