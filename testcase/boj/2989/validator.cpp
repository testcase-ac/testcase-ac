#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and K
    int N = inf.readInt(2, 300000, "N");
    inf.readSpace();
    int K = inf.readInt(1, 1000, "K");
    inf.readEoln();

    // Read the leaves: coordinates and flies
    vector<int> X(N+1), Y(N+1), F(N+1);
    // to ensure all coordinates are distinct
    map<pair<int,int>, int> coord2idx;
    // group by rows (same Y) and by columns (same X)
    const int MAXC = 100000;
    vector<vector<pair<int,int>>> byRow(MAXC+1), byCol(MAXC+1);

    for (int i = 1; i <= N; i++) {
        X[i] = inf.readInt(0, MAXC, "X_i");
        inf.readSpace();
        Y[i] = inf.readInt(0, MAXC, "Y_i");
        inf.readSpace();
        F[i] = inf.readInt(0, 1000, "F_i");
        inf.readEoln();

        // check distinctness
        pair<int,int> p = {X[i], Y[i]};
        ensuref(coord2idx.find(p) == coord2idx.end(),
                "Duplicate coordinate at leaf %d: (%d, %d)", i, X[i], Y[i]);
        coord2idx[p] = i;

        byRow[Y[i]].emplace_back(X[i], i);
        byCol[X[i]].emplace_back(Y[i], i);
    }

    // Build the directed graph: from each leaf, you can jump to the next leaf
    // in the same row (increasing X) or column (increasing Y).
    vector<vector<int>> adj(N+1);
    for (int y = 0; y <= MAXC; y++) {
        auto &v = byRow[y];
        if (v.size() <= 1) continue;
        sort(v.begin(), v.end());
        for (int j = 0; j + 1 < (int)v.size(); j++) {
            int u = v[j].second;
            int w = v[j+1].second;
            // edge u -> w
            adj[u].push_back(w);
        }
    }
    for (int x = 0; x <= MAXC; x++) {
        auto &v = byCol[x];
        if (v.size() <= 1) continue;
        sort(v.begin(), v.end());
        for (int j = 0; j + 1 < (int)v.size(); j++) {
            int u = v[j].second;
            int w = v[j+1].second;
            adj[u].push_back(w);
        }
    }

    // We perform a DP on the DAG: nodes sorted by (X+Y) increasing is a valid topological order
    vector<pair<int,int>> order;
    order.reserve(N);
    for (int i = 1; i <= N; i++) {
        order.emplace_back(X[i] + Y[i], i);
    }
    sort(order.begin(), order.end());

    const long long NEG_INF = LLONG_MIN / 4;
    vector<long long> dp(N+1, NEG_INF);
    // initial energy after eating flies on leaf 1
    dp[1] = F[1];

    // relax edges
    for (auto &pr : order) {
        int u = pr.second;
        if (dp[u] < K) continue; // cannot make any jump
        long long have = dp[u];
        for (int v : adj[u]) {
            long long cand = have - K + F[v];
            if (cand > dp[v]) {
                dp[v] = cand;
            }
        }
    }

    // Validate that it's always solvable: dp[N] >= 0 (we don't require dp[N] >= K,
    // because no more jumps needed after reaching N)
    ensuref(dp[N] >= 0,
            "Input guarantees a path exists, but computed dp[N]=%lld < 0", dp[N]);

    inf.readEof();
    return 0;
}
