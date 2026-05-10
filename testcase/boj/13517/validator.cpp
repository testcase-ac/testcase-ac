#include "testlib.h"
#include <vector>
#include <set>
#include <queue>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read N
    int N = inf.readInt(2, 100000, "N");
    inf.readEoln();

    // 2. Read weights
    vector<int> weights = inf.readInts(N, 1, 1000000, "weights");
    inf.readEoln();

    // 3. Read N-1 edges
    vector<vector<int>> adj(N+1); // 1-based
    set<pair<int,int>> edges;
    for (int i = 0; i < N-1; ++i) {
        int u = inf.readInt(1, N, "u");
        inf.readSpace();
        int v = inf.readInt(1, N, "v");
        inf.readEoln();

        ensuref(u != v, "Self-loop detected at edge %d: (%d, %d)", i+1, u, v);
        int a = min(u, v), b = max(u, v);
        ensuref(!edges.count({a, b}), "Multiple edge detected between %d and %d", a, b);
        edges.insert({a, b});
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // 4. Check connectivity and acyclicity (tree)
    // BFS from node 1
    vector<bool> visited(N+1, false);
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
                cnt++;
            }
        }
    }
    ensuref(cnt == N, "Graph is not connected: only %d out of %d nodes are reachable from node 1", cnt, N);

    // Check for cycles: since N-1 edges and connected, it's a tree, so no need for further check

    // 5. Read M
    int M = inf.readInt(1, 100000, "M");
    inf.readEoln();

    // 6. Read M queries
    for (int i = 0; i < M; ++i) {
        int u = inf.readInt(1, N, "query_u");
        inf.readSpace();
        int v = inf.readInt(1, N, "query_v");
        inf.readSpace();
        int k = inf.readInt(1, N, "query_k");
        inf.readEoln();
        // No further check: k can be up to N, but the path from u to v always exists in a tree
    }

    inf.readEof();
}
