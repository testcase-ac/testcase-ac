#include "testlib.h"
#include <vector>
#include <set>
#include <queue>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read N and Q
    int N = inf.readInt(1, 200000, "N");
    inf.readSpace();
    int Q = inf.readInt(1, 200000, "Q");
    inf.readEoln();

    // 2. Read parent array
    // parent[i] = parent of node i+2 (since i from 0 to N-2, node from 2 to N)
    vector<int> parent(N+1, 0); // parent[1] is unused (root)
    parent[1] = 0; // root has no parent

    for (int i = 2; i <= N; ++i) {
        int a = inf.readInt(1, N, "parent");
        inf.readEoln();
        parent[i] = a;
    }

    // 3. Validate tree structure
    // - No cycles
    // - Connected
    // - Root is 1, root has no parent
    // - Each node except root has exactly one parent
    // - No self-loop

    // Build adjacency list for undirected tree
    vector<vector<int>> adj(N+1);
    for (int i = 2; i <= N; ++i) {
        int p = parent[i];
        ensuref(p != i, "Self-loop detected at node %d", i);
        adj[i].push_back(p);
        adj[p].push_back(i);
    }

    // Check for cycles and connectivity using BFS
    vector<bool> visited(N+1, false);
    queue<int> q;
    q.push(1);
    visited[1] = true;
    int visit_cnt = 1;
    vector<int> par(N+1, 0);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : adj[u]) {
            if (!visited[v]) {
                visited[v] = true;
                par[v] = u;
                ++visit_cnt;
                q.push(v);
            } else if (par[u] != v) {
                // Found a back edge, which should not happen in a tree
                ensuref(false, "Cycle detected between %d and %d", u, v);
            }
        }
    }
    ensuref(visit_cnt == N, "Tree is not connected: only %d/%d nodes reachable from root", visit_cnt, N);

    // 4. Read Q queries and validate
    set<pair<int,int>> edge_set;
    for (int i = 2; i <= N; ++i) {
        int p = parent[i];
        int u = min(i, p), v = max(i, p);
        edge_set.insert({u, v});
    }

    for (int qidx = 0; qidx < Q; ++qidx) {
        int b = inf.readInt(1, N, "b");
        inf.readSpace();
        int c = inf.readInt(1, N, "c");
        inf.readSpace();
        int d = inf.readInt(0, 1, "d");
        inf.readEoln();

        ensuref(b != c, "Query %d: b and c must be different, got %d %d", qidx+1, b, c);
    }

    inf.readEof();
}
