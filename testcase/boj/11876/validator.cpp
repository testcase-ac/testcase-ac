#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "N");
    inf.readSpace();
    int k = inf.readInt(1, 50, "K");
    inf.readEoln();

    ensuref(k <= n, "K must not exceed N: K=%d, N=%d", k, n);

    inf.readLongs(n, 0LL, 1000000000LL, "a_i");
    inf.readEoln();
    inf.readEof();
}
