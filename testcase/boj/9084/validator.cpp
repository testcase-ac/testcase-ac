#include <cstdint>
#include <vector>
#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int T = inf.readInt(1, 10, "T");
    inf.readEoln();
    for (int tc = 1; tc <= T; tc++) {
        setTestCase(tc);

        int N = inf.readInt(1, 20, "N");
        inf.readEoln();

        vector<int> coins = inf.readInts(N, 1, 10000, "coin");
        inf.readEoln();
        for (int i = 1; i < N; i++) {
            ensuref(coins[i] > coins[i-1],
                    "Coins must be strictly increasing: coin[%d]=%d is not > coin[%d]=%d",
                    i, coins[i], i-1, coins[i-1]);
        }

        int M = inf.readInt(1, 10000, "M");
        inf.readEoln();

        const int64_t LIMIT = (int64_t(1) << 31) - 1;
        vector<int64_t> dp(M+1, 0);
        dp[0] = 1;
        for (int c : coins) {
            for (int j = c; j <= M; j++) {
                dp[j] += dp[j - c];
                if (dp[j] > LIMIT) {
                    dp[j] = LIMIT;
                }
            }
        }

        ensuref(dp[M] < LIMIT,
                "Number of ways to make %d with given coins is %lld, not less than 2^31-1",
                M, dp[M]);
    }

    inf.readEof();
    return 0;
}
