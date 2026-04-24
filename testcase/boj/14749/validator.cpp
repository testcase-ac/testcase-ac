#include "testlib.h"
#include <vector>
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

    // Read number of vertices
    int n = inf.readInt(2, 100000, "n");
    inf.readEoln();

    // Prepare DSU to check for cycles and connectivity
    DSU dsu(n);

    // Read edges
    for (int i = 1; i <= n - 1; i++) {
        int u = inf.readInt(1, n, "u_i");
        inf.readSpace();
        int v = inf.readInt(1, n, "v_i");
        inf.readEoln();

        // No loops allowed
        ensuref(u != v,
                "Loop detected at edge %d: (%d, %d)", i, u, v);

        // Check for cycle or multiple edge
        bool merged = dsu.unite(u, v);
        ensuref(merged,
                "Cycle or multiple edge detected at edge %d: (%d, %d)", i, u, v);
    }

    // Read start and end vertices
    int s = inf.readInt(1, n, "s");
    inf.readSpace();
    int t = inf.readInt(1, n, "t");
    inf.readEoln();

    // Start and end must be distinct
    ensuref(s != t,
            "Start and end vertices must be distinct but both are %d", s);

    // Check connectivity: all in one component
    int root1 = dsu.find(1);
    for (int i = 2; i <= n; i++) {
        ensuref(dsu.find(i) == root1,
                "Graph is disconnected: vertex %d is not reachable", i);
    }

    inf.readEof();
    return 0;
}
