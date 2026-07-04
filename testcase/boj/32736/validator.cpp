#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    constexpr int kMaxT = 10000;
    constexpr int kMaxSumN = 200000;
    constexpr long long kMinAi = -1000000000LL;
    constexpr long long kMaxAi = 1000000000LL;

    int t = inf.readInt(1, kMaxT, "t");
    inf.readEoln();

    int sumN = 0;
    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(1, kMaxSumN, "n");
        inf.readEoln();

        sumN += n;
        ensuref(sumN <= kMaxSumN, "sum of n exceeds %d after test case %d", kMaxSumN, tc);

        for (int i = 1; i <= n; ++i) {
            inf.readLong(kMinAi, kMaxAi, "a_i");
            if (i < n) {
                inf.readSpace();
            } else {
                inf.readEoln();
            }
        }
    }

    inf.readEof();
}
