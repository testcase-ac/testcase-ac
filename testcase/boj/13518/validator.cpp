#include "testlib.h"
#include <vector>
#include <set>
#include <queue>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read N
    int n = inf.readInt(2, 100000, "n");
    inf.readEoln();

    // 2. Read weights
    vector<int> weights = inf.readInts(n, 1, 1000000, "weight");
    inf.readEoln();

    // 3. Read edges
    vector<vector<int>> adj(n + 1); // 1-based
    set<pair<int, int>> edge_set;
    for (int i = 0; i < n - 1; ++i) {
        int u = inf.readInt(1, n, "u");
        inf.readSpace();
        int v = inf.readInt(1, n, "v");
        inf.readEoln();

        ensuref(u != v, "Self-loop detected at edge %d: (%d, %d)", i + 1, u, v);

        int a = min(u, v), b = max(u, v);
        ensuref(edge_set.count({a, b}) == 0, "Multiple edge detected between %d and %d", a, b);
        edge_set.insert({a, b});

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // 4. Check connectivity (tree property)
    // BFS from node 1, check all nodes are reachable
    vector<bool> visited(n + 1, false);
    queue<int> q;
    q.push(1);
    visited[1] = true;
    int cnt = 1;
    while (!q.empty()) {
        int cur = q.front(); q.pop();
        for (int nxt : adj[cur]) {
            if (!visited[nxt]) {
                visited[nxt] = true;
                q.push(nxt);
                ++cnt;
            }
        }
    }
    ensuref(cnt == n, "Graph is not connected: only %d out of %d nodes reachable from node 1", cnt, n);

    // 5. Check for cycles (tree property)
    // Since n-1 edges and connected, no need to check cycles separately

    // 6. Read M
    int m = inf.readInt(1, 100000, "m");
    inf.readEoln();

    // 7. Read queries
    for (int i = 0; i < m; ++i) {
        int u = inf.readInt(1, n, "query_u");
        inf.readSpace();
        int v = inf.readInt(1, n, "query_v");
        inf.readEoln();
        // No further constraints on queries
    }

    inf.readEof();
}
