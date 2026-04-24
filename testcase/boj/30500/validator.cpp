#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

struct DSU {
    vector<int> p;
    DSU(int n): p(n+1) { for (int i = 0; i <= n; i++) p[i] = i; }
    int find(int x) {
        return p[x] == x ? x : p[x] = find(p[x]);
    }
    void unite(int a, int b) {
        a = find(a); b = find(b);
        if (a != b) p[b] = a;
    }
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n, m
    int n = inf.readInt(2, 100000, "n");
    inf.readSpace();
    int m = inf.readInt(1, 1000000, "m");
    inf.readEoln();

    // Prepare DSU for connectivity
    DSU dsu(n);

    // Read edges
    vector<pair<int,int>> edges;
    edges.reserve(m);
    for (int i = 0; i < m; i++) {
        int a = inf.readInt(1, n, "a_i");
        inf.readSpace();
        int b = inf.readInt(1, n, "b_i");
        inf.readEoln();
        ensuref(a != b,
                "Loop detected at edge index %d: (%d, %d)", i, a, b);
        edges.emplace_back(a, b);
        dsu.unite(a, b);
    }

    // Check directed edge duplicates
    sort(edges.begin(), edges.end());
    for (int i = 1; i < m; i++) {
        if (edges[i] == edges[i-1]) {
            ensuref(false,
                    "Duplicate directed edge detected: (%d, %d)",
                    edges[i].first, edges[i].second);
        }
    }

    // Check undirected connectivity
    int root1 = dsu.find(1);
    for (int v = 2; v <= n; v++) {
        ensuref(dsu.find(v) == root1,
                "Graph is disconnected: node %d is not reachable from node 1", v);
    }

    inf.readEof();
    return 0;
}
