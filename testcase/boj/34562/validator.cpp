#include "testlib.h"
#include <set>
#include <vector>
#include <queue>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N, M, K
    int N = inf.readInt(2, 20, "N");
    inf.readSpace();
    int M = inf.readInt(1, 300000, "M");
    inf.readSpace();
    int K = inf.readInt(1, 100000, "K");
    inf.readEoln();

    // Prepare to check for multiple edges and loops
    set<pair<int, int>> edge_set;

    // Build adjacency list for connectivity check
    vector<vector<int>> adj(N + 1);

    for (int i = 0; i < M; ++i) {
        int a = inf.readInt(1, N, "a");
        inf.readSpace();
        int b = inf.readInt(1, N, "b");
        inf.readSpace();
        int c = inf.readInt(1, 100000, "c");
        inf.readEoln();

        ensuref(a != b, "Loop detected at edge index %d: (%d, %d)", i + 1, a, b);

        // For multiple edge check, store (min(a,b), max(a,b))
        int u = min(a, b), v = max(a, b);
        ensuref(!edge_set.count({u, v}), "Multiple edge detected at edge index %d: (%d, %d)", i + 1, a, b);
        edge_set.insert({u, v});

        // For connectivity check
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    // Check that the graph is connected
    vector<bool> vis(N + 1, false);
    queue<int> q;
    q.push(1);
    vis[1] = true;
    int cnt = 1;
    while (!q.empty()) {
        int cur = q.front(); q.pop();
        for (int nxt : adj[cur]) {
            if (!vis[nxt]) {
                vis[nxt] = true;
                q.push(nxt);
                ++cnt;
            }
        }
    }
    ensuref(cnt == N, "Graph is not connected: only %d out of %d nodes are reachable from node 1", cnt, N);

    inf.readEof();
}
