#include "testlib.h"
#include <vector>
#include <set>
using namespace std;

struct DSU {
    int n;
    vector<int> p, r;
    int comp;
    DSU(int _n) : n(_n), p(n), r(n, 0), comp(n) {
        for (int i = 0; i < n; i++) p[i] = i;
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
        comp--;
        return true;
    }
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);
    
    // Read N and K
    int N = inf.readInt(1, 200000, "N");
    inf.readSpace();
    int K = inf.readInt(1, 1000000, "K");
    inf.readEoln();
    
    // Prepare DSU and edge set
    DSU dsu(N);
    set<pair<int,int>> edges;
    
    // Read N-1 edges
    for (int i = 0; i < N - 1; i++) {
        int u = inf.readInt(0, N - 1, "u");
        inf.readSpace();
        int v = inf.readInt(0, N - 1, "v");
        inf.readSpace();
        int w = inf.readInt(0, 1000000, "w");
        inf.readEoln();
        
        // No loops
        ensuref(u != v,
                "Loop detected at edge index %d: (%d, %d)", i, u, v);
        
        // No multiple edges
        int a = min(u, v);
        int b = max(u, v);
        ensuref(!edges.count({a, b}),
                "Multiple edges detected at edge index %d: (%d, %d)", i, a, b);
        edges.insert({a, b});
        
        // Union in DSU
        dsu.unite(u, v);
    }
    
    // Check connectivity (for N >= 1, comp should be 1)
    ensuref(dsu.comp == 1,
            "Graph is not connected: %d components found (should be 1)", dsu.comp);
    
    inf.readEof();
    return 0;
}
