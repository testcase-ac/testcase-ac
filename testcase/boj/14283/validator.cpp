#include "testlib.h"
#include <vector>
#include <numeric>
using namespace std;

// DSU for connectivity check
struct DSU {
    vector<int> p;
    DSU(int n): p(n) { iota(p.begin(), p.end(), 0); }
    int find(int x) { return p[x] == x ? x : p[x] = find(p[x]); }
    void unite(int x, int y) { p[find(x)] = find(y); }
    bool same(int x, int y) { return find(x) == find(y); }
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 50, "n");
    inf.readSpace();
    int m = inf.readInt(1, 1000, "m");
    inf.readEoln();

    vector<tuple<int,int,int>> edges;
    for (int i = 0; i < m; ++i) {
        int a = inf.readInt(1, n, "a");
        inf.readSpace();
        int b = inf.readInt(1, n, "b");
        inf.readSpace();
        int c = inf.readInt(1, 100, "c");
        inf.readEoln();

        ensuref(a != b, "Edge %d: a == b (%d == %d), self-loop not allowed", i+1, a, b);

        edges.emplace_back(a-1, b-1, c); // 0-based for DSU
    }

    // Read s and t
    int s = inf.readInt(1, n, "s");
    inf.readSpace();
    int t = inf.readInt(1, n, "t");
    inf.readEoln();
    ensuref(s != t, "s == t (%d), s and t must be different", s);

    // Global property: all edges together must make the graph connected
    // Let's check that
    DSU dsu(n);
    for (const auto& e : edges) {
        int u, v, c;
        tie(u, v, c) = e;
        dsu.unite(u, v);
    }
    int root = dsu.find(0);
    for (int i = 1; i < n; ++i) {
        ensuref(dsu.find(i) == root, "Graph is not connected when all edges are added (node %d is not connected to node 1)", i+1);
    }

    inf.readEof();
}
