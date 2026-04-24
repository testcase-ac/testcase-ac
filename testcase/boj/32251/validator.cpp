#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

struct DSU {
    vector<int> p;
    int comps;
    DSU(int n): p(n+1), comps(n) {
        for (int i = 1; i <= n; i++) p[i] = i;
    }
    int find(int x) {
        return p[x] == x ? x : p[x] = find(p[x]);
    }
    void unite(int a, int b) {
        a = find(a); b = find(b);
        if (a != b) {
            p[b] = a;
            comps--;
        }
    }
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N, Q
    int N = inf.readInt(1, 100000, "N");
    inf.readSpace();
    int Q = inf.readInt(1, 100000, "Q");
    inf.readEoln();

    // Read edges, check loops, duplicates, and build DSU
    DSU dsu(N);
    set<pair<int,int>> edges;
    for (int i = 0; i < N-1; i++) {
        int u = inf.readInt(1, N, "u");
        inf.readSpace();
        int v = inf.readInt(1, N, "v");
        inf.readEoln();
        ensuref(u != v, "Loop detected on edge %d: %d-%d", i+1, u, v);
        int a = min(u, v), b = max(u, v);
        ensuref(!edges.count({a,b}), "Multiple edges detected between %d and %d", a, b);
        edges.insert({a,b});
        dsu.unite(u, v);
    }
    // Check connectivity
    ensuref(dsu.comps == 1, "Graph is not connected, has %d components", dsu.comps);

    // Read initial fruit sizes
    vector<long long> sizes = inf.readLongs(N, 1LL, 1000000000LL, "x_i");
    inf.readEoln();

    // Read queries
    int cntType2 = 0;
    for (int i = 0; i < Q; i++) {
        int type = inf.readInt(1, 2, "type");
        if (type == 1) {
            inf.readSpace();
            int u = inf.readInt(1, N, "u");
            inf.readSpace();
            int x = inf.readInt(1, 1000000000, "x");
            inf.readEoln();
        } else {
            // type == 2
            inf.readSpace();
            int u = inf.readInt(1, N, "u");
            inf.readEoln();
            cntType2++;
        }
    }
    ensuref(cntType2 > 0, "There must be at least one query of type 2");
    inf.readEof();
    return 0;
}
