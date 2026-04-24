#include "testlib.h"
#include <vector>
#include <queue>
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n and m
    int n = inf.readInt(1, 100, "n");
    inf.readSpace();
    int m = inf.readInt(1, 500, "m");
    inf.readEoln();

    // Prepare to collect edges and build adjacency for connectivity check
    set<pair<int,int>> seen;
    vector<vector<int>> adj(n+1);

    for (int i = 0; i < m; i++) {
        // Each edge line: u v w
        int u = inf.readInt(1, n, "u_i");
        inf.readSpace();
        int v = inf.readInt(1, n, "v_i");
        inf.readSpace();
        int w = inf.readInt(1, 500, "w_i");
        inf.readEoln();

        // No loops
        ensuref(u != v,
                "Self-loop detected on edge %d: (%d, %d)",
                i+1, u, v);

        // No multiple edges (undirected)
        int a = min(u, v), b = max(u, v);
        pair<int,int> e = make_pair(a, b);
        ensuref(!seen.count(e),
                "Multiple edge detected between %d and %d on edge %d",
                a, b, i+1);
        seen.insert(e);

        // Build adjacency
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // Check connectivity via BFS/DFS
    vector<char> vis(n+1, 0);
    queue<int> q;
    q.push(1);
    vis[1] = 1;
    int cnt = 1;
    while (!q.empty()) {
        int x = q.front(); q.pop();
        for (int y : adj[x]) {
            if (!vis[y]) {
                vis[y] = 1;
                cnt++;
                q.push(y);
            }
        }
    }
    ensuref(cnt == n,
            "Graph is not connected: only %d out of %d vertices are reachable",
            cnt, n);

    // No extra content
    inf.readEof();
    return 0;
}
