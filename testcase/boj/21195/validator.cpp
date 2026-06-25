#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "N");
    inf.readSpace();
    long long s = inf.readLong(1LL, 100000000LL, "S");
    inf.readEoln();

    long long minimumCredits = s * (n - 1LL);
    for (int i = 1; i <= n; ++i) {
        long long c = inf.readLong(1LL, 100000000LL, "C_i");
        ensuref(c >= minimumCredits,
                "C_%d must be at least S * (N - 1): %lld < %lld",
                i, c, minimumCredits);
        inf.readEoln();
    }

    inf.readEof();
}
