#include "testlib.h"
#include <set>
#include <vector>
#include <queue>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n, m, k
    int n = inf.readInt(2, 100000, "n");
    inf.readSpace();
    int m = inf.readInt(1, 100000, "m");
    inf.readSpace();
    int k = inf.readInt(2, 100000, "k");
    inf.readEoln();

    // For checking no loops and no multiple edges
    set<pair<int, int>> edge_set;

    // For connectivity check
    vector<vector<int>> adj(n + 1); // 1-based

    for (int i = 0; i < m; ++i) {
        int u = inf.readInt(1, n, "u_i");
        inf.readSpace();
        int v = inf.readInt(1, n, "v_i");
        inf.readSpace();
        int c = inf.readInt(0, k, "c_i");
        inf.readEoln();

        ensuref(u != v, "Loop detected at edge index %d: (%d, %d)", i + 1, u, v);

        int a = min(u, v), b = max(u, v);
        ensuref(!edge_set.count({a, b}), "Multiple edge detected between %d and %d (edge index %d)", u, v, i + 1);
        edge_set.insert({a, b});

        // For connectivity
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // Read a and b (capitals)
    int a = inf.readInt(1, n, "a");
    inf.readSpace();
    int b = inf.readInt(1, n, "b");
    inf.readEoln();
    ensuref(a != b, "Capitals must be different: a = %d, b = %d", a, b);

    // Check that the graph is connected
    vector<bool> vis(n + 1, false);
    queue<int> q;
    q.push(1);
    vis[1] = true;
    int cnt = 1;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : adj[u]) {
            if (!vis[v]) {
                vis[v] = true;
                q.push(v);
                ++cnt;
            }
        }
    }
    ensuref(cnt == n, "Graph is not connected: only %d out of %d nodes are reachable from node 1", cnt, n);

    inf.readEof();
}
