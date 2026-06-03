#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    long long n = inf.readLong(1LL, 1000000000LL, "N");
    inf.readSpace();
    int m = inf.readInt(0, 1000000, "M");
    inf.readEoln();

    ensuref(m < n, "M must be smaller than N, got M=%d and N=%lld", m, n);

    for (int i = 1; i <= m; ++i) {
        inf.readLong(1LL, n, "k_i");
        inf.readEoln();
    }

    inf.readEof();
}
