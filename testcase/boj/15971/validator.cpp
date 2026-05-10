#include "testlib.h"
#include <vector>
using namespace std;

struct DSU {
    vector<int> p, r;
    int comp;
    DSU(int n): p(n+1), r(n+1, 0), comp(n) {
        for (int i = 1; i <= n; i++) p[i] = i;
    }
    int find(int x) {
        return p[x] == x ? x : p[x] = find(p[x]);
    }
    // returns true if merged, false if already same component
    bool unite(int a, int b) {
        int pa = find(a), pb = find(b);
        if (pa == pb) return false;
        if (r[pa] < r[pb]) {
            p[pa] = pb;
        } else if (r[pb] < r[pa]) {
            p[pb] = pa;
        } else {
            p[pb] = pa;
            r[pa]++;
        }
        comp--;
        return true;
    }
    int components() const { return comp; }
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and robot positions
    int N = inf.readInt(1, 100000, "N");
    inf.readSpace();
    int r1 = inf.readInt(1, N, "r1");
    inf.readSpace();
    int r2 = inf.readInt(1, N, "r2");
    inf.readEoln();

    // Prepare DSU for checking tree structure
    DSU dsu(N);

    // Read edges
    for (int i = 0; i < N - 1; i++) {
        int a = inf.readInt(1, N, "a_i");
        inf.readSpace();
        int b = inf.readInt(1, N, "b_i");
        inf.readSpace();
        int w = inf.readInt(1, 1000, "w_i");
        inf.readEoln();

        // No loops
        ensuref(a != b,
                "Loop detected at edge index %d: (%d, %d)", i, a, b);

        // No cycles => unique simple path property
        bool merged = dsu.unite(a, b);
        ensuref(merged,
                "Cycle detected at edge index %d: (%d, %d)", i, a, b);
        // weight is already checked by readInt bounds
    }

    // Graph must be connected
    ensuref(dsu.components() == 1,
            "Graph is not connected: %d components found", dsu.components());

    inf.readEof();
    return 0;
}
