#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 10000, "N");
    inf.readSpace();
    int k = inf.readInt(2, 9, "K");
    inf.readEoln();

    ensuref(k <= n, "K must be at most N: N=%d, K=%d", n, k);

    inf.readEof();
}
