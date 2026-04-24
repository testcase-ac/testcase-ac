#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

struct DSU {
    vector<int> p, r;
    int comps;
    DSU(int n): p(n+1), r(n+1, 0), comps(n) {
        for (int i = 1; i <= n; i++) p[i] = i;
    }
    int find(int x) {
        return p[x] == x ? x : p[x] = find(p[x]);
    }
    // returns true if merged, false if already same set
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

    // Read N, M, C
    int N = inf.readInt(1, 200000, "N");
    inf.readSpace();
    int M = inf.readInt(1, 200000, "M");
    inf.readSpace();
    int C = inf.readInt(1, N, "C");
    inf.readEoln();

    // Read colors
    vector<int> color = inf.readInts(N, 1, C, "color");
    inf.readEoln();

    // Read tree edges
    DSU dsu(N);
    set<pair<int,int>> edges;
    for (int i = 1; i <= N-1; i++) {
        int u = inf.readInt(1, N, "u_i");
        inf.readSpace();
        int v = inf.readInt(1, N, "v_i");
        inf.readEoln();

        ensuref(u != v,
                "Loop detected at edge index %d: both endpoints are %d", i, u);
        int a = min(u, v), b = max(u, v);
        ensuref(!edges.count({a, b}),
                "Multiple edges detected at edge index %d: (%d, %d)", i, u, v);
        edges.insert({a, b});

        bool merged = dsu.unite(u, v);
        ensuref(merged,
                "Cycle detected at edge index %d: adding edge (%d, %d) creates a cycle", i, u, v);
    }
    // Ensure connectivity
    ensuref(dsu.comps == 1,
            "Graph is not connected: %d components remain", dsu.comps);

    // Read queries
    for (int i = 1; i <= M; i++) {
        int v = inf.readInt(1, N, "v_i");
        inf.readSpace();
        int c = inf.readInt(1, C, "c_i");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
