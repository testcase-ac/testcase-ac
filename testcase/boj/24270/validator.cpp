#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 500000, "N");
    inf.readSpace();
    long long k = inf.readLong(1LL, 1000000000LL, "K");
    inf.readEoln();

    long long total = 0;
    for (int i = 0; i < n; ++i) {
        if (i > 0) {
            inf.readSpace();
        }
        long long s = inf.readLong(1LL, k, "S_i");
        total += s;
        ensuref(total <= k,
                "sum of S_i exceeds K after index %d: total=%lld, K=%lld",
                i + 1, total, k);
    }
    inf.readEoln();

    inf.readEof();
}
