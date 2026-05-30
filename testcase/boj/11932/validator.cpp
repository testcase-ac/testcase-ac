#include "testlib.h"
#include <vector>
#include <set>
#include <algorithm>
#include <limits>
using namespace std;

const int MAXN = 100000;
const int MAXM = 100000;
const int LOG = 17;

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

    vector<int> weights = inf.readInts(n, numeric_limits<int>::min(), numeric_limits<int>::max(), "weight");
    inf.readEoln();

    set<int> weight_set(weights.begin(), weights.end());
    ensuref((int)weight_set.size() == n, "All weights must be distinct");

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

        dsu.unite(u, v);
    }

    int root = dsu.find(1);
    for (int i = 2; i <= n; ++i) {
        ensuref(dsu.find(i) == root, "Graph is not connected: node %d is not connected to node 1", i);
    }

    ensuref((int)edge_set.size() == n-1, "Number of edges is not N-1");

    vector<int> depth(n + 1, -1);
    vector<vector<int>> up(LOG + 1, vector<int>(n + 1, 0));
    vector<int> stack;
    stack.push_back(1);
    depth[1] = 0;

    while (!stack.empty()) {
        int u = stack.back();
        stack.pop_back();
        for (int v : adj[u]) {
            if (v == up[0][u]) {
                continue;
            }
            up[0][v] = u;
            depth[v] = depth[u] + 1;
            stack.push_back(v);
        }
    }

    for (int j = 1; j <= LOG; ++j) {
        for (int v = 1; v <= n; ++v) {
            up[j][v] = up[j - 1][up[j - 1][v]];
        }
    }

    for (int i = 0; i < m; ++i) {
        int x = inf.readInt(1, n, "X");
        inf.readSpace();
        int y = inf.readInt(1, n, "Y");
        inf.readSpace();
        int k = inf.readInt(1, n, "K");
        inf.readEoln();

        int u = x, v = y;
        if (depth[u] < depth[v]) {
            swap(u, v);
        }

        int diff = depth[u] - depth[v];
        for (int j = LOG; j >= 0; --j) {
            if (diff & (1 << j)) {
                u = up[j][u];
            }
        }

        if (u != v) {
            for (int j = LOG; j >= 0; --j) {
                if (up[j][u] != up[j][v]) {
                    u = up[j][u];
                    v = up[j][v];
                }
            }
            u = up[0][u];
        }

        int lca = u;
        int path_len = depth[x] + depth[y] - 2 * depth[lca] + 1;

        ensuref(k >= 1 && k <= path_len, "Query %d: K=%d is not in [1, path_len=%d] for X=%d, Y=%d", i+1, k, path_len, x, y);
    }

    inf.readEof();
}
