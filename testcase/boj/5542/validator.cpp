#include "testlib.h"
#include <vector>
#include <set>
#include <queue>
#include <algorithm>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read N, M, K, Q
    int N = inf.readInt(2, 100000, "N");
    inf.readSpace();
    int M = inf.readInt(1, 200000, "M");
    inf.readSpace();
    int K = inf.readInt(1, N, "K");
    inf.readSpace();
    int Q = inf.readInt(1, 100000, "Q");
    inf.readEoln();

    // 2. Read M edges, check 1 <= u,v <= N, 1 <= w <= 1000, no self-loops, no multi-edges
    vector<vector<pair<int,int>>> adj(N+1); // 1-based
    set<pair<int,int>> edge_set;
    for (int i = 0; i < M; ++i) {
        int u = inf.readInt(1, N, "u");
        inf.readSpace();
        int v = inf.readInt(1, N, "v");
        inf.readSpace();
        int w = inf.readInt(1, 1000, "w");
        inf.readEoln();

        ensuref(u != v, "Self-loop detected at edge %d: (%d, %d)", i+1, u, v);

        int a = min(u, v), b = max(u, v);
        ensuref(!edge_set.count({a, b}), "Multiple edge detected between %d and %d", a, b);
        edge_set.insert({a, b});

        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);
    }

    // 3. Check that the graph is connected (BFS/DFS)
    vector<bool> vis(N+1, false);
    queue<int> q;
    q.push(1);
    vis[1] = true;
    int vis_cnt = 1;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (auto& p : adj[u]) {
            int v = p.first;
            if (!vis[v]) {
                vis[v] = true;
                ++vis_cnt;
                q.push(v);
            }
        }
    }
    ensuref(vis_cnt == N, "Graph is not connected: only %d/%d nodes reachable from node 1", vis_cnt, N);

    // 4. Read K festival cities, check 1 <= city <= N, no duplicates
    set<int> festival;
    for (int i = 0; i < K; ++i) {
        int f = inf.readInt(1, N, "festival_city");
        inf.readEoln();
        ensuref(!festival.count(f), "Duplicate festival city: %d", f);
        festival.insert(f);
    }

    // 5. Read Q queries, check 1 <= s,t <= N, s != t
    for (int i = 0; i < Q; ++i) {
        int s = inf.readInt(1, N, "start_city");
        inf.readSpace();
        int t = inf.readInt(1, N, "end_city");
        inf.readEoln();
        ensuref(s != t, "Query %d: start and end city must be different, got %d %d", i+1, s, t);
    }

    inf.readEof();
}
