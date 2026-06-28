#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    long long n = inf.readLong(1LL, 1000000000LL, "N");
    inf.readSpace();
    long long m = inf.readLong(1LL, 1000000000000000000LL, "M");
    inf.readSpace();
    int k = inf.readInt(1, 10000, "K");
    inf.readEoln();

    ensuref(k <= m, "K must be at most M, got K=%d and M=%lld", k, m);

    long long previousDay = 0;
    for (int i = 1; i <= k; ++i) {
        long long a = inf.readLong(1LL, m, "A_i");
        inf.readSpace();
        long long b = inf.readLong(1LL, n, "B_i");
        inf.readEoln();

        ensuref(previousDay < a,
                "A_i must be strictly increasing at index %d: previous=%lld current=%lld",
                i, previousDay, a);
        previousDay = a;
    }

    inf.readEof();
}
