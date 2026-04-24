#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;
using int64 = long long;
const int64 LIMIT = 2147483647LL;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(3, 100, "N");
    inf.readEoln();

    // Read M
    int M = inf.readInt(3, 100, "M");
    inf.readEoln();

    // Read relations
    vector<vector<pair<int,int64>>> adj(N+1);
    vector<int> indegree(N+1);
    for (int i = 0; i < M; i++) {
        int X = inf.readInt(1, N, "X_i");
        inf.readSpace();
        int Y = inf.readInt(1, N, "Y_i");
        inf.readSpace();
        int64 K = inf.readLong(1LL, LIMIT, "K_i");
        inf.readEoln();
        adj[X].push_back({Y, K});
        indegree[Y]++;
    }

    // Final product must have at least one recipe
    ensuref(!adj[N].empty(), "Final product %d has no dependency relations", N);
    // https://www.acmicpc.net/board/view/34641
    // 어떤 장난감 완제품과 그에 필요한 부품들이 주어진다고 했으므로 완제품에 필요하지 않은 부품이 입력으로 주어지는 것은 문제의 설정에 어긋난다
    for(int i=1; i<N; i++) {
        ensuref(indegree[i] > 0, "Product %d is not used by any other product", i);
    }

    // Check acyclicity via Kahn's algorithm
    vector<int> indeg(N+1, 0);
    for (int u = 1; u <= N; u++) {
        for (auto &e : adj[u]) {
            int v = e.first;
            indeg[v]++;
        }
    }
    queue<int> q;
    for (int u = 1; u <= N; u++) {
        if (indeg[u] == 0) q.push(u);
    }
    vector<int> topo;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        topo.push_back(u);
        for (auto &e : adj[u]) {
            int v = e.first;
            indeg[v]--;
            if (indeg[v] == 0) q.push(v);
        }
    }
    ensuref((int)topo.size() == N, "Cycle detected in part dependency graph");

    // Identify basic parts: those with no outgoing edges
    vector<bool> is_basic(N+1, false);
    for (int u = 1; u <= N; u++) {
        if (adj[u].empty()) {
            is_basic[u] = true;
        }
    }

    // DP to compute required basic counts
    // dp[u][i] = number of basic part i needed for one unit of u
    vector<vector<__int128_t>> dp(N+1, vector<__int128_t>(N+1, 0));
    // Process nodes in reverse topological order
    for (int idx = N-1; idx >= 0; idx--) {
        int u = topo[idx];
        if (is_basic[u]) {
            dp[u][u] = 1;  // basic part needs itself
        } else {
            // intermediate or final product
            for (auto &pr : adj[u]) {
                int v = pr.first;
                int64 k = pr.second;
                // accumulate dp[v] * k into dp[u]
                for (int i = 1; i <= N; i++) {
                    if (dp[v][i] == 0) continue;
                    __int128_t add = (__int128_t)k * dp[v][i];
                    dp[u][i] += add;
                    // check bounds
                    ensuref(dp[u][i] <= LIMIT,
                            "Required count for basic part %d in assembling part %d exceeds limit %lld",
                            i, u, LIMIT);
                }
            }
        }
    }

    // Validate final product counts
    __int128_t totalSum = 0;
    for (int i = 1; i <= N; i++) {
        if (!is_basic[i]) continue;
        if (dp[N][i] > 0) {
            totalSum += dp[N][i];
            ensuref(totalSum <= LIMIT,
                    "Total required basic parts for final product %d exceeds limit %lld",
                    N, LIMIT);
        }
    }

    inf.readEof();
    return 0;
}
