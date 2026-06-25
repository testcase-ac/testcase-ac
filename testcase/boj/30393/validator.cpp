#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    constexpr int MAX_N = 500000;
    constexpr int MOD = 998244353;

    int n = inf.readInt(1, MAX_N, "N");
    inf.readSpace();
    int m = inf.readInt(1, MOD - 1, "M");
    inf.readEoln();

    long long sum = 0;
    for (int i = 1; i <= n; ++i) {
        int ai = inf.readInt(1, MOD - 1, "A_i");
        sum += ai;
        ensuref(sum < MOD, "sum A_i must be less than %d, got %lld", MOD, sum);

        if (i < n) {
            inf.readSpace();
        } else {
            inf.readEoln();
        }
    }

    ensuref(m <= sum, "M must not exceed sum A_i: M=%d, sum=%lld", m, sum);
    inf.readEof();
}
