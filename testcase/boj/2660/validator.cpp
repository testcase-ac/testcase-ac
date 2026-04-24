#include "testlib.h"
#include <vector>
#include <queue>
#include <cassert>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of members
    int n = inf.readInt(1, 50, "n");
    inf.readEoln();

    // Adjacency matrix to detect duplicates and self-loops
    vector<vector<bool>> adj(n+1, vector<bool>(n+1, false));
    bool seen_sentinel = false;
    int line_no = 1;

    // Read edges until sentinel "-1 -1"
    while (true) {
        ++line_no;
        int u = inf.readInt(-1, n, "u");
        inf.readSpace();
        int v = inf.readInt(-1, n, "v");
        inf.readEoln();

        // Sentinel check
        if (u == -1 || v == -1) {
            ensuref(u == -1 && v == -1,
                    "Line %d: both numbers must be -1 for sentinel, got (%d, %d)",
                    line_no, u, v);
            seen_sentinel = true;
            break;
        }

        // Validate normal edge endpoints
        ensuref(1 <= u && u <= n, "Line %d: u = %d out of range [1, %d]", line_no, u, n);
        ensuref(1 <= v && v <= n, "Line %d: v = %d out of range [1, %d]", line_no, v, n);
        ensuref(u != v,
                "Line %d: self-loop detected at node %d", line_no, u);
        ensuref(!adj[u][v],
                "Line %d: multiple edge detected between %d and %d", line_no, u, v);
        // store undirected edge
        adj[u][v] = adj[v][u] = true;
    }

    // Must have seen sentinel
    ensuref(seen_sentinel, "No sentinel (-1 -1) found");

    // Graph connectivity check
    // If n >= 1, run BFS from node 1
    if (n >= 1) {
        vector<bool> vis(n+1, false);
        queue<int> q;
        vis[1] = true;
        q.push(1);
        int count = 1;
        while (!q.empty()) {
            int x = q.front(); q.pop();
            for (int y = 1; y <= n; y++) {
                if (adj[x][y] && !vis[y]) {
                    vis[y] = true;
                    q.push(y);
                    count++;
                }
            }
        }
        ensuref(count == n,
                "Graph is not connected: only %d out of %d nodes are reachable from node 1",
                count, n);
    }

    // Compute eccentricities and check distances are finite
    vector<int> ecc(n+1, 0);
    for (int s = 1; s <= n; s++) {
        vector<int> dist(n+1, -1);
        queue<int> q;
        dist[s] = 0;
        q.push(s);
        while (!q.empty()) {
            int x = q.front(); q.pop();
            for (int y = 1; y <= n; y++) {
                if (adj[x][y] && dist[y] == -1) {
                    dist[y] = dist[x] + 1;
                    q.push(y);
                }
            }
        }
        int maxd = 0;
        for (int t = 1; t <= n; t++) {
            if (s == t) continue;
            ensuref(dist[t] != -1,
                    "Node %d cannot reach node %d, graph should be connected", s, t);
            maxd = max(maxd, dist[t]);
        }
        ecc[s] = maxd;
    }
    // The score (eccentricity) is at least 0 and at most n-1
    for (int i = 1; i <= n; i++) {
        ensuref(0 <= ecc[i] && ecc[i] <= n-1,
                "Computed eccentricity for node %d is %d, out of valid range [0, %d]",
                i, ecc[i], n-1);
    }

    inf.readEof();
    return 0;
}
