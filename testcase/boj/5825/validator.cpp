#include "testlib.h"
#include <vector>
#include <set>
#include <queue>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int n = inf.readInt(1, 100000, "n");
    inf.readEoln();

    // Prepare to read edges
    vector<vector<pair<int, int>>> adj(n + 1); // 1-based indexing
    set<pair<int, int>> edge_set;

    for (int i = 0; i < n - 1; ++i) {
        int a = inf.readInt(1, n, "a_i");
        inf.readSpace();
        int b = inf.readInt(1, n, "b_i");
        inf.readSpace();
        int t = inf.readInt(0, 1, "t_i");
        inf.readEoln();

        ensuref(a != b, "Self-loop detected at edge %d: (%d, %d)", i + 1, a, b);

        // Check for multiple edges (undirected)
        int u = min(a, b), v = max(a, b);
        ensuref(!edge_set.count({u, v}), "Multiple edge detected between %d and %d", u, v);
        edge_set.insert({u, v});

        // Build adjacency list for connectivity check
        adj[a].emplace_back(b, t);
        adj[b].emplace_back(a, t);
    }

    // Check connectivity (BFS)
    vector<bool> visited(n + 1, false);
    queue<int> q;
    q.push(1);
    visited[1] = true;
    int cnt = 1;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (auto &p : adj[u]) {
            int v = p.first;
            if (!visited[v]) {
                visited[v] = true;
                q.push(v);
                ++cnt;
            }
        }
    }
    ensuref(cnt == n, "Graph is not connected: only %d out of %d nodes are reachable from node 1", cnt, n);

    inf.readEof();
}
