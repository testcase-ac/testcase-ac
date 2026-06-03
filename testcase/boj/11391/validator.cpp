#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 16, "N");
    inf.readSpace();
    int k = inf.readInt(1, 15, "K");
    inf.readEoln();
    ensuref(k < n, "K must be less than N, got K=%d and N=%d", k, n);

    inf.readEof();
}
