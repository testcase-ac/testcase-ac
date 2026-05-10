#include "testlib.h"
#include <set>
#include <vector>
#include <queue>
#include <limits>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and M
    int N = inf.readInt(2, 1000, "N");
    inf.readSpace();
    int M = inf.readInt(1, 100000, "M");
    inf.readEoln();

    // Prepare to check for multiple edges and build adjacency list
    set<pair<int, int>> edge_set;
    vector<vector<pair<int, int>>> adj(N + 1); // 1-based indexing

    for (int i = 0; i < M; ++i) {
        int A = inf.readInt(1, N, "A");
        inf.readSpace();
        int B = inf.readInt(1, N, "B");
        inf.readSpace();
        int C = inf.readInt(1, 10000, "C");
        inf.readEoln();

        ensuref(A != B, "Self-loop detected at edge %d: (%d, %d)", i + 1, A, B);

        int u = min(A, B), v = max(A, B);
        ensuref(!edge_set.count({u, v}), "Multiple edge detected between %d and %d", u, v);
        edge_set.insert({u, v});

        adj[A].emplace_back(B, C);
        adj[B].emplace_back(A, C);
    }

    // Check that the graph is connected (since S=1, T=2, both must be reachable)
    vector<bool> vis(N + 1, false);
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
    ensuref(cnt == N, "Graph is not connected: only %d out of %d nodes reachable from node 1", cnt, N);

    inf.readEof();
}
