#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const long long maxS = 1000000000000000000LL;
    const long long maxIntervalDelta = 1000000LL;
    const long long maxE = maxS + maxIntervalDelta;

    long long s = inf.readLong(2LL, maxS, "s");
    inf.readSpace();
    long long e = inf.readLong(102LL, maxE, "e");
    inf.readSpace();
    int k = inf.readInt(1, 900000, "k");
    inf.readEoln();

    long long delta = e - s;
    ensuref(100LL <= delta && delta <= maxIntervalDelta,
            "e - s must be in [100, 1000000], got %lld", delta);

    long long length = delta + 1;
    ensuref(10LL * k <= 9LL * length,
            "k must be at most 0.9 * (e - s + 1), got k=%d and length=%lld",
            k, length);

    inf.readEof();
}
