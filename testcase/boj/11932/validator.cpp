#include "testlib.h"
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

const int MAXN = 100000;
const int MAXM = 100000;

struct DSU {
    vector<int> p;
    DSU(int n) : p(n+1) {
        for (int i = 1; i <= n; ++i) p[i] = i;
    }
    int find(int x) {
        if (p[x] != x) p[x] = find(p[x]);
        return p[x];
    }
    bool unite(int x, int y) {
        x = find(x); y = find(y);
        if (x == y) return false;
        p[x] = y;
        return true;
    }
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, MAXN, "n");
    inf.readSpace();
    int m = inf.readInt(1, MAXM, "m");
    inf.readEoln();

    // Read weights
    vector<int> weights = inf.readInts(n, -2147483648, 2147483647, "weight");
    inf.readEoln();

    // Check all weights are distinct
    set<int> weight_set(weights.begin(), weights.end());
    ensuref((int)weight_set.size() == n, "All weights must be distinct");

    // Read edges
    vector<vector<int>> adj(n+1);
    set<pair<int,int>> edge_set;
    DSU dsu(n);
    for (int i = 0; i < n-1; ++i) {
        int u = inf.readInt(1, n, "X");
        inf.readSpace();
        int v = inf.readInt(1, n, "Y");
        inf.readEoln();

        ensuref(u != v, "Self-loop detected at edge %d: (%d, %d)", i+1, u, v);
        int a = min(u, v), b = max(u, v);
        ensuref(!edge_set.count({a, b}), "Multiple edge detected at edge %d: (%d, %d)", i+1, u, v);
        edge_set.insert({a, b});

        adj[u].push_back(v);
        adj[v].push_back(u);

        // For connectivity check
        dsu.unite(u, v);
    }

    // Check that the graph is connected (tree)
    int root = dsu.find(1);
    for (int i = 2; i <= n; ++i) {
        ensuref(dsu.find(i) == root, "Graph is not connected: node %d is not connected to node 1", i);
    }

    // Check for cycles (tree property)
    ensuref((int)edge_set.size() == n-1, "Number of edges is not N-1");

    // Check for acyclicity using DFS (optional, as DSU already checks for cycles)
    // But let's check for single component and no cycles
    // (DSU already ensures no cycles if unite returns false, but let's be thorough)
    // Already done above.

    // Read queries
    for (int i = 0; i < m; ++i) {
        int x = inf.readInt(1, n, "X");
        inf.readSpace();
        int y = inf.readInt(1, n, "Y");
        inf.readSpace();
        int k = inf.readInt(1, n, "K");
        inf.readEoln();

        // The path from x to y always exists in a tree, so no need to check that.

        // The number of nodes on the path from x to y is at least 1 and at most n.
        // But K must be between 1 and the number of nodes on the path from x to y.
        // So we need to compute the number of nodes on the path from x to y.

        // But since the problem says "K is at least 1 and at most the number of nodes on the path from x to y",
        // we must check that K <= path length.

        // Let's compute the path length using BFS or DFS parent array.
        // Precompute parent and depth for all nodes.

        static vector<int> parent, depth;
        if (i == 0) {
            parent.assign(n+1, -1);
            depth.assign(n+1, -1);
            vector<int> stack;
            stack.push_back(1);
            depth[1] = 0;
            parent[1] = 0;
            while (!stack.empty()) {
                int u = stack.back(); stack.pop_back();
                for (int v : adj[u]) {
                    if (depth[v] == -1) {
                        depth[v] = depth[u] + 1;
                        parent[v] = u;
                        stack.push_back(v);
                    }
                }
            }
        }

        // Compute LCA to get path length
        int u = x, v = y;
        int du = depth[u], dv = depth[v];
        int cnt = 0;
        // Move up to same depth
        while (du > dv) { u = parent[u]; du--; }
        while (dv > du) { v = parent[v]; dv--; }
        while (u != v) { u = parent[u]; v = parent[v]; }
        int lca = u;
        int path_len = depth[x] + depth[y] - 2 * depth[lca] + 1;

        ensuref(k >= 1 && k <= path_len, "Query %d: K=%d is not in [1, path_len=%d] for X=%d, Y=%d", i+1, k, path_len, x, y);
    }

    inf.readEof();
}
