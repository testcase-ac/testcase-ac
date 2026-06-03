#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    constexpr int kMaxT = 100000;
    constexpr int kMaxTotalN = 100000;
    constexpr int kMaxA = (1 << 30) - 1;

    int t = inf.readInt(1, kMaxT, "T");
    inf.readEoln();

    long long total_n = 0;
    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(1, kMaxTotalN, "N");
        inf.readEoln();

        total_n += n;
        ensuref(total_n <= kMaxTotalN,
                "sum of N exceeds %d after test case %d: %lld",
                kMaxTotalN,
                tc,
                total_n);

        inf.readInts(n, 0, kMaxA, "A_i");
        inf.readEoln();
    }

    inf.readEof();
}
