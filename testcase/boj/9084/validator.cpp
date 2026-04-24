#include "testlib.h"
#include <vector>
#include <cstdint>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of test cases
    int T = inf.readInt(1, 10, "T");
    inf.readEoln();
    for (int tc = 1; tc <= T; tc++) {
        setTestCase(tc);

        // Read N
        int N = inf.readInt(1, 20, "N");
        inf.readEoln();

        // Read coin denominations
        vector<int> coins = inf.readInts(N, 1, 10000, "coin");
        inf.readEoln();
        // Check sorted strictly increasing (no duplicates)
        for (int i = 1; i < N; i++) {
            ensuref(coins[i] > coins[i-1],
                    "Coins must be strictly increasing: coin[%d]=%d is not > coin[%d]=%d",
                    i, coins[i], i-1, coins[i-1]);
        }

        // Read target amount M
        int M = inf.readInt(1, 10000, "M");
        inf.readEoln();

        // Compute number of ways to make amount M using classic DP
        const int64_t LIMIT = (int64_t(1) << 31) - 1; // 2^31-1
        vector<int64_t> dp(M+1, 0);
        dp[0] = 1;
        for (int c : coins) {
            for (int j = c; j <= M; j++) {
                dp[j] += dp[j - c];
                // We only need to check final dp[M], but to be safe, ensure no overflow
                ensuref(dp[j] >= 0 && dp[j] <= LIMIT,
                        "Intermediate dp[%d] = %lld exceeds allowed bound [0, %lld]",
                        j, dp[j], LIMIT);
            }
        }
        // Validate the problem statement guarantee: number of ways < 2^31-1
        ensuref(dp[M] <= LIMIT,
                "Number of ways to make %d with given coins is %lld, exceeds 2^31-1",
                M, dp[M]);
    }

    inf.readEof();
    return 0;
}
