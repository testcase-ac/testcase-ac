#include "testlib.h"
#include <vector>
#include <queue>
#include <set>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of vertices and edges
    int n = inf.readInt(1, 100, "n");
    inf.readSpace();
    // m must satisfy n-1 <= m <= n+15
    int m = inf.readInt(n - 1, n + 15, "m");
    inf.readEoln();

    // Prepare adjacency and edge set for checks
    vector<vector<int>> adj(n + 1);
    set<pair<int,int>> seen;
    for (int i = 0; i < m; i++) {
        int a = inf.readInt(1, n, "a_i");
        inf.readSpace();
        int b = inf.readInt(1, n, "b_i");
        inf.readEoln();

        // No loops allowed
        ensuref(a != b,
                "Loop detected at edge %d: (%d, %d)",
                i+1, a, b);

        // Check for multiple edges: normalize order
        int u = min(a, b), v = max(a, b);
        pair<int,int> e = make_pair(u, v);
        ensuref(!seen.count(e),
                "Multiple edge detected at edge %d: (%d, %d)",
                i+1, a, b);
        seen.insert(e);

        // Build adjacency
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    // Check connectivity via BFS
    vector<char> vis(n + 1, false);
    queue<int> q;
    // start BFS from vertex 1 (always exists since n>=1)
    q.push(1);
    vis[1] = true;
    int cnt = 1;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : adj[u]) {
            if (!vis[v]) {
                vis[v] = true;
                cnt++;
                q.push(v);
            }
        }
    }
    ensuref(cnt == n,
            "Graph is not connected: only %d out of %d vertices reachable",
            cnt, n);

    // Final checks: exactly one newline after last line and then EOF
    inf.readEof();
    return 0;
}
