#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000000, "N");
    inf.readSpace();
    long long l = inf.readLong(1LL, 1000000000LL, "L");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        int k = inf.readInt(1, 100000, "K_i");
        inf.readSpace();
        int t = inf.readInt(1, 100000, "T_i");
        inf.readEoln();

        long long product = 1LL * k * t;
        ensuref(product <= l, "K_i * T_i exceeds L at problem %d: %lld > %lld", i, product, l);
    }

    inf.readEof();
}
