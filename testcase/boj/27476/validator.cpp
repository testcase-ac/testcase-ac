#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    constexpr int kMaxTests = 1000;
    constexpr int kMinN = 2;
    constexpr int kMaxTotalN = 200000;
    constexpr long long kMinAi = -500000000LL;
    constexpr long long kMaxAi = 500000000LL;

    int t = inf.readInt(1, kMaxTests, "t");
    inf.readEoln();

    int totalN = 0;
    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(kMinN, kMaxTotalN, "n");
        inf.readEoln();
        totalN += n;
        ensuref(totalN <= kMaxTotalN, "sum of n exceeds %d", kMaxTotalN);

        for (int i = 1; i <= n; ++i) {
            inf.readLong(kMinAi, kMaxAi, "a_i");
            if (i == n) {
                inf.readEoln();
            } else {
                inf.readSpace();
            }
        }
    }

    inf.readEof();
}
