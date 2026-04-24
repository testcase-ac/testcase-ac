#include "testlib.h"
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

struct DSU {
    vector<int> p, r;
    int comps;
    DSU(int n): p(n+1), r(n+1,0), comps(n) {
        for (int i = 1; i <= n; i++) p[i] = i;
    }
    int find(int x) {
        if (p[x] != x) p[x] = find(p[x]);
        return p[x];
    }
    bool unite(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) return false;
        if (r[a] < r[b]) swap(a, b);
        p[b] = a;
        if (r[a] == r[b]) r[a]++;
        comps--;
        return true;
    }
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of nodes
    int N = inf.readInt(2, 100000, "N");
    inf.readEoln();

    // Prepare to check edges
    DSU dsu(N);
    set<pair<int,int>> edges;
    int M = N - 1;

    for (int i = 0; i < M; i++) {
        int u = inf.readInt(1, N, "u_i");
        inf.readSpace();
        int v = inf.readInt(1, N, "v_i");
        inf.readEoln();

        // No loops
        ensuref(u != v,
                "Loop detected at edge index %d: (%d, %d)", i, u, v);

        // No multiple edges
        pair<int,int> e = (u < v ? make_pair(u,v) : make_pair(v,u));
        ensuref(edges.insert(e).second,
                "Multiple edges detected at edge index %d: (%d, %d)", i, u, v);

        // No cycles
        ensuref(dsu.unite(u, v),
                "Cycle detected at edge index %d: (%d, %d)", i, u, v);
    }

    // The graph must be connected => exactly 1 component
    ensuref(dsu.comps == 1,
            "The graph is disconnected: %d components", dsu.comps);

    inf.readEof();
    return 0;
}
