#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "N");
    inf.readSpace();
    int k = inf.readInt(1, 26, "K");
    inf.readEoln();

    ensuref(k <= n, "K must be at most N, got N=%d K=%d", n, k);

    inf.readEof();
}
