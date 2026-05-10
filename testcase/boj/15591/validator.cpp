#include "testlib.h"
#include <vector>
#include <queue>
#include <set>
using namespace std;

// DSU for checking tree property (no cycles, connected)
struct DSU {
    vector<int> p;
    DSU(int n): p(n+1) {
        for (int i = 1; i <= n; ++i) p[i] = i;
    }
    int find(int x) {
        return p[x] == x ? x : p[x] = find(p[x]);
    }
    bool unite(int x, int y) {
        x = find(x), y = find(y);
        if (x == y) return false;
        p[y] = x;
        return true;
    }
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read N and Q
    int N = inf.readInt(1, 5000, "N");
    inf.readSpace();
    int Q = inf.readInt(1, 5000, "Q");
    inf.readEoln();

    // 2. Read N-1 edges, check:
    // - 1 <= p_i, q_i <= N
    // - 1 <= r_i <= 1e9
    // - No loops (p_i != q_i)
    // - No multiple edges
    // - The graph is a tree (connected, no cycles)
    set<pair<int,int>> edges;
    DSU dsu(N);
    for (int i = 0; i < N-1; ++i) {
        int p = inf.readInt(1, N, "p_i");
        inf.readSpace();
        int q = inf.readInt(1, N, "q_i");
        inf.readSpace();
        int r = inf.readInt(1, 1000000000, "r_i");
        inf.readEoln();

        ensuref(p != q, "Loop detected at edge %d: (%d, %d)", i+1, p, q);

        int a = min(p, q), b = max(p, q);
        ensuref(!edges.count({a, b}), "Multiple edge detected between %d and %d", a, b);
        edges.insert({a, b});

        ensuref(dsu.unite(p, q), "Cycle detected at edge %d: (%d, %d)", i+1, p, q);
    }
    // After all edges, check that all nodes are connected (single component)
    int root = dsu.find(1);
    for (int i = 2; i <= N; ++i) {
        ensuref(dsu.find(i) == root, "Graph is not connected: node %d is not connected to node 1", i);
    }

    // 3. Read Q queries, check:
    // - 1 <= k_i <= 1e9
    // - 1 <= v_i <= N
    for (int i = 0; i < Q; ++i) {
        int k = inf.readInt(1, 1000000000, "k_i");
        inf.readSpace();
        int v = inf.readInt(1, N, "v_i");
        inf.readEoln();
    }

    inf.readEof();
}
