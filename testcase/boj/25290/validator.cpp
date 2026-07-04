#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 100, "T");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        long long n = inf.readLong(3LL, 9999LL, "N");
        inf.readSpace();
        long long maxK = n * n - 2;
        long long k = inf.readLong(1LL, maxK, "K");
        inf.readEoln();

        ensuref(n % 2 == 1, "N must be odd, got %lld", n);
        ensuref(k < n * n - 1, "K must be strictly less than N^2 - 1");
    }

    inf.readEof();
}
