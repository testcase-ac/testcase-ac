#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read magic string (pattern)
    string pattern = inf.readLine("[RINGS]{1,20}", "pattern");
    int m = pattern.size();
    // Read devil's bridge string
    string A = inf.readLine("[RINGS]{1,100}", "devil");
    // Read angel's bridge string
    string B = inf.readLine("[RINGS]{1,100}", "angel");

    // Validate lengths
    int n = A.size();
    ensuref(n >= 1, "Length of bridge strings must be at least 1, got %d", n);
    ensuref((int)B.size() == n,
            "Lengths of devil (%d) and angel (%d) strings differ", n, (int)B.size());

    // Compute number of ways via DP and ensure answer <= 2^31-1
    // dp[k][j][r]: number of ways to match first k chars of pattern,
    // ending at position j (0-based) on row r (0 = A, 1 = B).
    vector<vector<array<long long,2>>> dp(m+1, vector<array<long long,2>>(n, {0,0}));

    // Initialization for k = 1
    for (int j = 0; j < n; j++) {
        if (A[j] == pattern[0]) dp[1][j][0] = 1;
        if (B[j] == pattern[0]) dp[1][j][1] = 1;
    }

    // Fill DP for k = 2..m
    for (int k = 2; k <= m; k++) {
        char want = pattern[k-1];
        for (int j = 0; j < n; j++) {
            // row 0 -> devil A, previous must be on row 1
            if (A[j] == want) {
                long long sum = 0;
                for (int p = 0; p < j; p++) {
                    sum += dp[k-1][p][1];
                }
                dp[k][j][0] = sum;
            }
            // row 1 -> angel B, previous must be on row 0
            if (B[j] == want) {
                long long sum = 0;
                for (int p = 0; p < j; p++) {
                    sum += dp[k-1][p][0];
                }
                dp[k][j][1] = sum;
            }
        }
    }

    // Sum up ways to match full pattern of length m
    long long total = 0;
    for (int j = 0; j < n; j++) {
        total += dp[m][j][0];
        total += dp[m][j][1];
    }

    // Ensure total ways fits in 2^31-1
    const long long LIMIT = 2147483647LL;
    ensuref(total <= LIMIT,
            "Number of ways (%lld) exceeds 2^31-1", total);

    inf.readEof();
    return 0;
}
