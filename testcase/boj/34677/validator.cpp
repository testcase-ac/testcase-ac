#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int MAXN = 3000;

    int n = inf.readInt(1, MAXN, "n");
    inf.readEoln();

    vector<int> A = inf.readInts(n, 1, n, "A_i");
    inf.readEoln();
    vector<int> B = inf.readInts(n, 1, n, "B_i");
    inf.readEoln();

    // Check that A is a permutation of 1..n
    {
        vector<int> cnt(n + 1, 0);
        for (int i = 0; i < n; ++i) {
            int v = A[i];
            ensuref(cnt[v] == 0, "A is not a permutation: value %d appears more than once", v);
            cnt[v] = 1;
        }
        // Since range is already checked [1, n], and all distinct, it's permutation
    }

    // Check that B is a permutation of 1..n
    {
        vector<int> cnt(n + 1, 0);
        for (int i = 0; i < n; ++i) {
            int v = B[i];
            ensuref(cnt[v] == 0, "B is not a permutation: value %d appears more than once", v);
            cnt[v] = 1;
        }
    }

    // Now verify the global property that an optimal partition always exists,
    // i.e., compute minimal k and check it is between 1 and n.
    // We actually compute minimal number of segments with the given condition
    // by dynamic programming over segment endpoints.

    // Precompute prefix minima for A and B to allow O(1) segment minimum queries.
    // prefMinPosA[i][j] = position of minimum in A[i..j], but that is O(n^2) memory.
    // Instead, precompute range minima with O(n^2) time and O(1) extra memory
    // on the fly for all (l,r) pairs and store only whether the minima positions match.
    int N = n;
    vector<vector<char>> good(N, vector<char>(N, 0));

    // For each left endpoint l, sweep r to the right maintaining current minima.
    for (int l = 0; l < N; ++l) {
        int minPosA = l;
        int minPosB = l;
        for (int r = l; r < N; ++r) {
            if (A[r] < A[minPosA]) minPosA = r;
            if (B[r] < B[minPosB]) minPosB = r;
            if (minPosA == minPosB) good[l][r] = 1;
        }
    }

    // DP: dp[i] minimal segments to cover prefix [0..i-1]
    const int INF = N + 5;
    vector<int> dp(N + 1, INF);
    dp[0] = 0;
    for (int i = 0; i < N; ++i) {
        if (dp[i] == INF) continue;
        for (int j = i; j < N; ++j) {
            if (good[i][j]) {
                dp[j + 1] = min(dp[j + 1], dp[i] + 1);
            }
        }
    }

    int k = dp[N];
    ensuref(1 <= k && k <= N, "No valid partition found, but statement guarantees it should exist");

    inf.readEof();
}
