#include "testlib.h"
#include <vector>
#include <queue>
#include <algorithm>
#include <set>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read N
    int N = inf.readInt(1, 100000, "N");
    inf.readEoln();

    // 2. Read A, B, C
    vector<int> friends(3);
    for (int i = 0; i < 3; ++i) {
        friends[i] = inf.readInt(1, N, string("friend_") + char('A'+i));
        if (i < 2) inf.readSpace();
    }
    inf.readEoln();

    // 3. Read M
    int M = inf.readInt(N-1, 500000, "M");
    inf.readEoln();

    // 4. Read M edges
    // Validate: 1 <= D, E <= N, 1 <= L <= 10000
    // No self-loops, no multiple edges (undirected)
    // The graph is connected (guaranteed by statement, must check)
    // Road is bidirectional

    // Use adjacency list for connectivity check
    vector<vector<pair<int,int>>> adj(N+1); // 1-based
    set<pair<int,int>> edge_set;

    for (int i = 0; i < M; ++i) {
        int D = inf.readInt(1, N, "D");
        inf.readSpace();
        int E = inf.readInt(1, N, "E");
        inf.readSpace();
        int L = inf.readInt(1, 10000, "L");
        inf.readEoln();

        ensuref(D != E, "Self-loop detected at edge %d: (%d, %d)", i+1, D, E);

        int u = min(D, E), v = max(D, E);
        ensuref(!edge_set.count({u, v}), "Multiple edge detected between %d and %d at edge %d", u, v, i+1);
        edge_set.insert({u, v});

        adj[D].emplace_back(E, L);
        adj[E].emplace_back(D, L);
    }

    // 5. Check connectivity (BFS/DFS)
    vector<bool> vis(N+1, false);
    queue<int> q;
    q.push(1);
    vis[1] = true;
    int cnt = 1;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (auto &p : adj[u]) {
            int v = p.first;
            if (!vis[v]) {
                vis[v] = true;
                q.push(v);
                ++cnt;
            }
        }
    }
    ensuref(cnt == N, "Graph is not connected: only %d out of %d nodes are reachable from node 1", cnt, N);

    inf.readEof();
}
