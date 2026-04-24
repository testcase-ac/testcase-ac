#include "testlib.h"
#include <vector>
#include <set>
using namespace std;

struct DSU {
    vector<int> p;
    DSU(int n): p(n+1) {
        for (int i = 0; i <= n; i++) p[i] = i;
    }
    int find(int x) {
        return p[x] == x ? x : (p[x] = find(p[x]));
    }
    void unite(int a, int b) {
        a = find(a); b = find(b);
        if (a != b) p[b] = a;
    }
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of nodes
    int n = inf.readInt(4, 100000, "n");
    inf.readEoln();

    int m = n - 1;
    DSU dsu(n);
    vector<int> deg(n+1, 0);
    set<pair<int,int>> edges;

    for (int i = 0; i < m; i++) {
        // Read edge: a b l
        int a = inf.readInt(1, n, "a_i");
        inf.readSpace();
        int b = inf.readInt(1, n, "b_i");
        ensuref(a != b, "Loop detected at edge index %d: (%d,%d)", i, a, b);
        inf.readSpace();
        int l = inf.readInt(1, 50, "l_i");
        inf.readEoln();

        // Check multiple edges
        int u = min(a, b), v = max(a, b);
        ensuref(!edges.count({u, v}),
                "Multiple edges detected at edge index %d: (%d,%d)", i, u, v);
        edges.insert({u, v});

        // Build DSU and degree count
        dsu.unite(a, b);
        deg[a]++; deg[b]++;
    }

    // Check connectivity
    int comps = 0;
    for (int i = 1; i <= n; i++) {
        if (dsu.find(i) == i) comps++;
    }
    ensuref(comps == 1, "Graph is not connected: has %d components", comps);

    // Check degree constraints: internal nodes have degree 3, leaves degree 1
    int cnt1 = 0, cnt3 = 0;
    for (int i = 1; i <= n; i++) {
        if (deg[i] == 1) {
            cnt1++;
        } else if (deg[i] == 3) {
            cnt3++;
        } else {
            ensuref(false, "Node %d has invalid degree %d; must be 1 or 3", i, deg[i]);
        }
    }
    // For a tree with internal deg-3 nodes, #leaves = #internal + 2
    ensuref(cnt1 == cnt3 + 2,
            "Invalid leaf/internal count: leaves=%d, internal_deg3=%d (expect leaves = internal+2)",
            cnt1, cnt3);

    inf.readEof();
    return 0;
}
