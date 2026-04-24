#include "testlib.h"
#include <vector>
#include <set>
using namespace std;

struct DSU {
    vector<int> p;
    DSU(int n): p(n+1, -1) {}
    int find(int x) {
        return p[x] < 0 ? x : p[x] = find(p[x]);
    }
    bool unite(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) return false;
        if (p[a] > p[b]) swap(a,b);
        p[a] += p[b];
        p[b] = a;
        return true;
    }
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of cities
    int n = inf.readInt(1, 30000, "n");
    inf.readEoln();

    // Tree edges: must be n-1, no loops, no multi-edges, no cycles, connected
    DSU dsu(n);
    set<pair<int,int>> edges;
    for (int i = 0; i < n-1; i++) {
        int a = inf.readInt(1, n, "a_i");
        inf.readSpace();
        int b = inf.readInt(1, n, "b_i");
        inf.readEoln();

        // no self-loop
        ensuref(a != b,
                "Loop detected at edge index %d: (%d,%d)", i, a, b);

        // no multiple edges
        pair<int,int> e = make_pair(a, b);
        pair<int,int> rev = make_pair(b, a);
        ensuref(!edges.count(e) && !edges.count(rev),
                "Multiple edges detected at edge index %d: (%d,%d)", i, a, b);
        edges.insert(e);
        edges.insert(rev);

        // no cycles
        bool merged = dsu.unite(a, b);
        ensuref(merged,
                "Cycle detected at edge index %d: (%d,%d)", i, a, b);
    }

    // Check connectivity: exactly one component
    int comps = 0;
    for (int i = 1; i <= n; i++) {
        if (dsu.find(i) == i) comps++;
    }
    ensuref(comps == 1, "Graph is not connected: %d components found", comps);

    // Number of visits
    int m = inf.readInt(1, 5000, "m");
    inf.readEoln();

    // Visit sequence
    for (int i = 0; i < m; i++) {
        int v = inf.readInt(1, n, "visit_i");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
