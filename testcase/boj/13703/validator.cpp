#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int k = inf.readInt(0, 63, "k");
    inf.readSpace();
    int n = inf.readInt(0, 63, "n");
    inf.readEoln();

    ensuref(k <= n, "expected k <= n, got k=%d and n=%d", k, n);

    inf.readEof();
}
