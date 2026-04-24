#include "testlib.h"
#include <vector>
#include <set>
using namespace std;

struct DSU {
    vector<int> p, r;
    DSU(int n): p(n+1), r(n+1, 0) {
        for (int i = 1; i <= n; i++) p[i] = i;
    }
    int find(int x) {
        return p[x] == x ? x : p[x] = find(p[x]);
    }
    bool unite(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) return false;
        if (r[a] < r[b]) swap(a, b);
        p[b] = a;
        if (r[a] == r[b]) r[a]++;
        return true;
    }
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N, S, D
    int N = inf.readInt(1, 100000, "N");
    inf.readSpace();
    int S = inf.readInt(1, N, "S");
    inf.readSpace();
    int D = inf.readInt(0, N, "D");
    inf.readEoln();

    // Prepare DSU and edge set
    DSU dsu(N);
    set<pair<int,int>> edges;
    
    // Read N-1 edges
    for (int i = 0; i < N-1; i++) {
        int x = inf.readInt(1, N, "x_i");
        inf.readSpace();
        int y = inf.readInt(1, N, "y_i");
        inf.readEoln();
        ensuref(x != y, "Loop detected at edge %d: (%d, %d)", i+1, x, y);
        int u = min(x,y), v = max(x,y);
        pair<int,int> e = make_pair(u,v);
        ensuref(!edges.count(e), "Multiple edge detected at index %d: (%d, %d)", i+1, u, v);
        edges.insert(e);
        // Check for cycles
        bool merged = dsu.unite(u, v);
        ensuref(merged, "Cycle detected when adding edge %d: (%d, %d)", i+1, u, v);
    }

    // Check connectivity: all nodes should be in one component
    int root = dsu.find(1);
    for (int i = 2; i <= N; i++) {
        ensuref(dsu.find(i) == root, "Graph is disconnected: node %d is unreachable", i);
    }

    inf.readEof();
    return 0;
}
