#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

// Helper function to compute the number of non-decreasing sequences of length n, sum m, all >= 1
// dp[n][m][last] is not needed since non-decreasing, we can always keep track of min value
// We use memoization to speed up the computation
long long count_sequences(int n, int m, int min_val, vector<vector<long long>>& dp) {
    // dp[n][m] = number of non-decreasing sequences of length n, sum m, all elements >= min_val
    if (n == 0) return m == 0 ? 1 : 0;
    if (m < n * min_val) return 0;
    if (m > n * 220) return 0; // impossible, since each Ai <= 220 (since M <= 220)
    if (dp[n][m] != -1) return dp[n][m];
    long long res = 0;
    for (int x = min_val; x <= m - (n - 1) * min_val; ++x) {
        res += count_sequences(n - 1, m - x, x, dp);
        if (res > 2147483647LL) break; // No need to count more than K's max
    }
    dp[n][m] = res;
    return res;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N, M, K
    int N = inf.readInt(1, 10, "N");
    inf.readSpace();
    int M = inf.readInt(1, 220, "M");
    inf.readSpace();
    int K = inf.readInt(1, 2147483647, "K");
    inf.readEoln();

    // Check that there is at least one valid sequence
    ensuref(M >= N, "Sum M=%d is too small for N=%d (all Ai >= 1)", M, N);

    // Compute the number of valid sequences
    vector<vector<long long>> dp(N + 1, vector<long long>(M + 1, -1));
    long long total = count_sequences(N, M, 1, dp);

    ensuref(total >= K, "There are only %lld valid sequences, but K=%d", total, K);

    inf.readEof();
}
