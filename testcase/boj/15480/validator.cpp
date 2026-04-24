#include "testlib.h"
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

struct DSU {
    int n;
    vector<int> p, r;
    int comps;
    DSU(int _n): n(_n), p(n+1), r(n+1, 0), comps(n) {
        for(int i = 1; i <= n; i++) p[i] = i;
    }
    int find(int x) {
        return p[x] == x ? x : p[x] = find(p[x]);
    }
    bool unite(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) return false;
        if (r[a] < r[b]) swap(a,b);
        p[b] = a;
        if (r[a] == r[b]) r[a]++;
        comps--;
        return true;
    }
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of nodes
    int N = inf.readInt(1, 100000, "N");
    inf.readEoln();

    // Read edges
    DSU dsu(N);
    set<pair<int,int>> edges;
    for (int i = 0; i < N-1; i++) {
        int u = inf.readInt(1, N, "u");
        inf.readSpace();
        int v = inf.readInt(1, N, "v");
        inf.readEoln();
        ensuref(u != v, "Loop detected on edge %d: (%d, %d)", i+1, u, v);
        int a = min(u,v), b = max(u,v);
        ensuref(!edges.count({a,b}), "Multiple edges detected on edge %d: (%d, %d)", i+1, u, v);
        edges.insert({a,b});
        dsu.unite(u, v);
    }

    // Ensure connectivity
    ensuref(dsu.comps == 1, "The tree is not connected: %d components found, expected 1", dsu.comps);

    // Read number of queries
    int M = inf.readInt(1, 100000, "M");
    inf.readEoln();

    // Read queries
    for (int i = 0; i < M; i++) {
        int r = inf.readInt(1, N, "r");
        inf.readSpace();
        int u = inf.readInt(1, N, "u");
        inf.readSpace();
        int v = inf.readInt(1, N, "v");
        inf.readEoln();
        // No further validation needed for queries: r,u,v in range
    }

    inf.readEof();
    return 0;
}
