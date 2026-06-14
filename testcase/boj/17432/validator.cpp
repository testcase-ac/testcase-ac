#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: The statement does not give an upper bound for T; use the local
    // default cap for unspecified test case counts.
    int t = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        long long n = inf.readLong(1LL, 100000LL, "N");
        inf.readSpace();
        long long m = inf.readLong(0LL, 4999950000LL, "M");
        inf.readEoln();

        long long maxInversions = n * (n - 1) / 2;
        ensuref(m <= maxInversions,
                "M must not exceed N*(N-1)/2: N=%lld, M=%lld, max=%lld",
                n, m, maxInversions);
    }

    inf.readEof();
}
