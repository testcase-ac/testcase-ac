#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

// We allocate dp globally to avoid stack overflow.
// dp[l][r][k]: minimum extra cost (sum of remW * dist) to turn off all lamps
// in [l..r], currently at endpoint k (0 -> l, 1 -> r).
static long long dp[1002][1002][2];

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N, M
    int N = inf.readInt(1, 1000, "N");
    inf.readSpace();
    int M = inf.readInt(1, N, "M");
    inf.readEoln();

    // Read D and W
    vector<int> D(N+1);
    vector<long long> W(N+1);
    for (int i = 1; i <= N; i++) {
        D[i] = inf.readInt(0, 1000, "D_i");
        inf.readSpace();
        W[i] = inf.readLong(1LL, 100000000LL, "W_i");
        inf.readEoln();
        if (i > 1) {
            ensuref(D[i] > D[i-1],
                    "Positions must be strictly increasing: D[%d]=%d, D[%d]=%d",
                    i-1, D[i-1], i, D[i]);
        }
    }

    // Prefix sums of W to compute remaining weight quickly
    vector<long long> prefixW(N+1, 0);
    for (int i = 1; i <= N; i++) {
        prefixW[i] = prefixW[i-1] + W[i];
    }
    long long totW = prefixW[N];

    // Initialize dp with INF
    const long long INF = LLONG_MAX / 4;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            dp[i][j][0] = dp[i][j][1] = INF;
        }
    }
    // Starting state: only lamp M is off, cost = 0, location is D[M]
    dp[M][M][0] = dp[M][M][1] = 0;

    // Expand intervals [l..r] that include M
    for (int len = 1; len <= N; len++) {
        for (int l = 1; l + len - 1 <= N; l++) {
            int r = l + len - 1;
            if (l > M || r < M) continue;  // must include starting lamp

            // total remaining power consumption of lamps still on
            long long remW = totW - (prefixW[r] - prefixW[l-1]);

            for (int k = 0; k < 2; k++) {
                long long cur = dp[l][r][k];
                if (cur >= INF) continue;
                int pos = (k == 0 ? D[l] : D[r]);

                // Turn off lamp at l-1 next (if exists)
                if (l > 1) {
                    int d = abs(pos - D[l-1]);
                    __int128 add = (__int128)remW * d;
                    long long costAdd = (long long)add;
                    dp[l-1][r][0] = min(dp[l-1][r][0], cur + costAdd);
                }
                // Turn off lamp at r+1 next (if exists)
                if (r < N) {
                    int d = abs(D[r+1] - pos);
                    __int128 add = (__int128)remW * d;
                    long long costAdd = (long long)add;
                    dp[l][r+1][1] = min(dp[l][r+1][1], cur + costAdd);
                }
            }
        }
    }

    // Final answer: all lamps off
    long long ans = min(dp[1][N][0], dp[1][N][1]);
    // Validate the problem statement's guarantee
    ensuref(ans < 1000000000LL,
            "Computed minimum wasted power %lld is not less than 1e9", ans);

    inf.readEof();
    return 0;
}
