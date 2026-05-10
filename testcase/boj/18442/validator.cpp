#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

using int64 = long long;
using i128 = __int128_t;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read V, P, L
    int V = inf.readInt(1, 20, "V");
    inf.readSpace();
    int P = inf.readInt(1, V, "P");
    inf.readSpace();
    long long L = inf.readLong(1LL, 1000000000000LL, "L");
    inf.readEoln();

    // Read village positions
    vector<long long> a = inf.readLongs(V, 0LL, L - 1, "a_i");
    inf.readEoln();

    // Check non-decreasing order
    for (int i = 1; i < V; ++i) {
        ensuref(a[i - 1] <= a[i],
                "village positions must be non-decreasing: a[%d]=%lld, a[%d]=%lld",
                i - 1, a[i - 1], i, a[i]);
    }

    // Sanity: V in range of constraint (already via readInt), also that L>0 already checked.

    // --- Global property check: given villages on circle and P, optimal solution exists ---
    // It is obvious from problem definition, but we can still sanity-check that computing
    // objective doesn't overflow and is consistent.

    // Precompute for each linearization (cut point) an optimal solution cost to ensure
    // that the cost fits in 64-bit and everything is well-defined.
    // Complexity: V <= 20, P <= 20 => we can afford O(V^4 * P).

    auto compute_min_cost_linear = [&](const vector<long long>& x) -> long long {
        int n = (int)x.size();
        // Precompute cost for serving contiguous segment [i, j] (0-based) with 1 post office.
        static long long cost[21][21];
        for (int i = 0; i < n; ++i) {
            for (int j = i; j < n; ++j) {
                int len = j - i + 1;
                int mid = i + len / 2;
                // Sum distances to median
                i128 s = 0;
                for (int k = i; k <= j; ++k) {
                    s += (i128) llabs(x[k] - x[mid]);
                }
                ensuref(s <= (i128)4e18, "segment cost overflow");
                cost[i][j] = (long long) s;
            }
        }

        const long long INF = (long long)4e18;
        static long long dp[21][21];
        for (int i = 0; i <= P; ++i)
            for (int j = 0; j <= n; ++j)
                dp[i][j] = INF;
        dp[0][0] = 0;

        for (int k = 1; k <= P; ++k) {
            for (int i = 1; i <= n; ++i) {
                long long best = INF;
                for (int t = 0; t < i; ++t) {
                    if (dp[k-1][t] == INF) continue;
                    long long cur = dp[k-1][t] + cost[t][i-1];
                    if (cur < best) best = cur;
                }
                dp[k][i] = best;
            }
        }
        long long ans = dp[P][n];
        ensuref(ans < INF, "internal DP cost is infinite (no solution?)");
        return ans;
    };

    // Build extended array for all possible cuts
    vector<long long> ext(2 * V);
    for (int i = 0; i < 2 * V; ++i) {
        ext[i] = a[i % V] + (i / V) * L;
    }

    long long globalBest = (long long)4e18;
    for (int cut = 0; cut < V; ++cut) {
        vector<long long> lin(V);
        for (int i = 0; i < V; ++i) {
            lin[i] = ext[cut + i] - ext[cut];
        }
        long long cur = compute_min_cost_linear(lin);
        if (cur < globalBest) globalBest = cur;
    }
    ensuref(globalBest < (long long)4e18,
            "computed global minimal cost overflow / no feasible configuration");

    inf.readEof();
}
