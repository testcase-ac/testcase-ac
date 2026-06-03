#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 1000, "N");
    inf.readSpace();
    long long d = inf.readLong(1LL, 1000000000LL, "D");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        long long t = inf.readLong(0LL, d, "T_i");
        inf.readSpace();
        long long k = inf.readLong(1LL, 1000000000LL, "K_i");
        inf.readEoln();

        ensuref(t % k == 0, "T_%d must be a multiple of K_%d, got T=%lld K=%lld",
                i, i, t, k);
    }

    inf.readEof();
}
