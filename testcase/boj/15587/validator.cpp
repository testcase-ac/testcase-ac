#include "testlib.h"
#include <vector>
#include <set>
#include <numeric>
using namespace std;

struct DSU {
    vector<int> p;
    DSU(int n): p(n) { iota(p.begin(), p.end(), 0); }
    int find(int x) {
        return p[x] == x ? x : (p[x] = find(p[x]));
    }
    // returns true if merged, false if already same component
    bool unite(int x, int y) {
        int rx = find(x), ry = find(y);
        if (rx == ry) return false;
        p[ry] = rx;
        return true;
    }
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and K
    int N = inf.readInt(2, 100000, "N");
    inf.readSpace();
    int K = inf.readInt(1, N, "K");
    inf.readEoln();

    // Prepare DSU and edge set for detecting cycles and multi-edges
    DSU dsu(N+1);
    set<pair<int,int>> seen;

    // Read N-1 edges
    for (int i = 1; i <= N-1; i++) {
        int u = inf.readInt(1, N, "u_i");
        inf.readSpace();
        int v = inf.readInt(1, N, "v_i");
        inf.readEoln();

        // No loops
        ensuref(u != v,
                "Loop detected at edge %d: (%d, %d)", i, u, v);

        // No multiple edges
        int a = min(u, v), b = max(u, v);
        ensuref(!seen.count({a, b}),
                "Multiple edges detected at edge %d: (%d, %d)", i, u, v);
        seen.insert({a, b});

        // No cycles
        ensuref(dsu.unite(u, v),
                "Cycle detected at edge %d: (%d, %d)", i, u, v);
    }

    // Since we have exactly N-1 edges and no cycles, the graph is connected
    // (an acyclic graph with N-1 edges on N nodes is necessarily connected)

    inf.readEof();
    return 0;
}
