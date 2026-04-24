#include "testlib.h"
#include <vector>
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

    // Read number of vertices
    int n = inf.readInt(1, 10000, "n");
    inf.readEoln();

    // Read weights
    vector<int> w = inf.readInts(n, 1, 10000, "w_i");
    inf.readEoln();

    // Prepare DSU for cycle and connectivity checks
    DSU dsu(n);

    // Read exactly n-1 edges
    for (int i = 0; i < n - 1; i++) {
        int u = inf.readInt(1, n, "u_i");
        inf.readSpace();
        int v = inf.readInt(1, n, "v_i");
        inf.readEoln();

        // No self-loops
        ensuref(u != v, "Loop detected at edge index %d: (%d, %d)", i, u, v);
        // No cycles or multiple edges
        bool merged = dsu.unite(u, v);
        ensuref(merged, "Cycle or multiple edges detected at edge index %d: (%d, %d)", i, u, v);
    }

    // Check connectivity: exactly one component
    int comps = 0;
    for (int i = 1; i <= n; i++) {
        if (dsu.find(i) == i) comps++;
    }
    ensuref(comps == 1, "Graph is not connected: %d components found", comps);

    inf.readEof();
    return 0;
}
