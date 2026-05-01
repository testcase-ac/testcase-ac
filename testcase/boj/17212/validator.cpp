#include "testlib.h"
#include <vector>
#include <algorithm>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Single integer N (0 ≤ N ≤ 100000), canonical decimal form
    int N = inf.readInt(0, 100000, "N");
    inf.readEoln();

    // Problem guarantees: answer always exists (i.e., N is always representable
    // using coins {1,2,5,7}) and is at most something trivial (≤ N).
    // Since coin 1 exists, representability is trivial for all N ≥ 0.
    // We additionally check that the minimal number of coins is within int
    // and consistent by computing it via DP (this also enforces any implied
    // "answer always exists" guarantee).

    const int INF = 1e9;
    vector<int> dp(N + 1, INF);
    dp[0] = 0;
    int coins[4] = {1, 2, 5, 7};

    for (int i = 1; i <= N; ++i) {
        for (int c : coins) {
            if (i - c >= 0 && dp[i - c] + 1 < dp[i]) {
                dp[i] = dp[i - c] + 1;
            }
        }
        // Every amount must be representable because of coin 1.
        ensuref(dp[i] < INF, "Amount %d is not representable with given coins", i);
    }

    // Also ensure the coin count is not absurd (should never fire, defensive)
    ensuref(dp[N] >= 0 && dp[N] <= N, "Computed minimal coin count out of range for N=%d", N);

    inf.readEof();
}
