#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int T = inf.readInt(1, 10, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);

        long long n = inf.readLong(1LL, 20000000000LL, "n");
        inf.readSpace();
        long long k = inf.readLong(0LL, 40000000000LL, "k");
        inf.readEoln();

        ensuref((__int128)k <= (__int128)2 * n,
                "k must be at most 2n, got n=%lld and k=%lld", n, k);
    }

    inf.readEof();
}
