#include "testlib.h"
#include <vector>
#include <set>
#include <queue>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(2, 100000, "N");
    inf.readEoln();

    // Prepare to read edges
    vector<vector<int>> adj(N + 1);
    set<pair<int, int>> edges;

    for (int i = 0; i < N - 1; ++i) {
        int a = inf.readInt(1, N, "a");
        inf.readSpace();
        int b = inf.readInt(1, N, "b");
        inf.readEoln();

        ensuref(a != b, "Self-loop detected at edge %d: (%d, %d)", i + 1, a, b);

        int u = min(a, b), v = max(a, b);
        ensuref(edges.count({u, v}) == 0, "Multiple edge detected between %d and %d", u, v);
        edges.insert({u, v});

        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    // Check that the graph is connected (i.e., is a tree)
    vector<bool> visited(N + 1, false);
    queue<int> q;
    q.push(1);
    visited[1] = true;
    int cnt = 1;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : adj[u]) {
            if (!visited[v]) {
                visited[v] = true;
                q.push(v);
                ++cnt;
            }
        }
    }
    ensuref(cnt == N, "Graph is not connected: only %d out of %d nodes are reachable from node 1", cnt, N);

    inf.readEof();
}
