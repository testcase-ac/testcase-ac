#include "testlib.h"
#include <vector>
#include <queue>
#include <set>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read n
    int n = inf.readInt(1, 100000, "n");
    inf.readEoln();

    // 2. Read edges
    vector<vector<int>> adj(n + 1);
    set<pair<int, int>> edges;
    for (int i = 0; i < n - 1; ++i) {
        int u = inf.readInt(1, n, "u");
        inf.readSpace();
        int v = inf.readInt(1, n, "v");
        inf.readEoln();

        ensuref(u != v, "Self-loop detected at edge %d: (%d, %d)", i + 1, u, v);

        int a = min(u, v), b = max(u, v);
        ensuref(!edges.count({a, b}), "Multiple edge detected at edge %d: (%d, %d)", i + 1, u, v);
        edges.insert({a, b});

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // 3. Check that the graph is connected and acyclic (i.e., is a tree)
    vector<bool> visited(n + 1, false);
    queue<int> q;
    q.push(1);
    visited[1] = true;
    int visit_cnt = 1;

    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : adj[u]) {
            if (!visited[v]) {
                visited[v] = true;
                ++visit_cnt;
                q.push(v);
            }
        }
    }
    ensuref(visit_cnt == n, "Graph is not connected: only %d out of %d nodes are reachable from root 1", visit_cnt, n);

    // 4. Check for cycles (should not be possible, but let's check for safety)
    // Since we already checked for multiple edges and self-loops, and the number of edges is n-1, and the graph is connected,
    // the graph must be a tree. No further cycle check is needed.

    inf.readEof();
}
