#include "testlib.h"
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

struct DSU {
    vector<int> p;
    DSU(int n): p(n+1, -1) {}
    int find(int x) {
        return p[x] < 0 ? x : p[x] = find(p[x]);
    }
    // returns true if merged, false if already in same set
    bool unite(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) return false;
        if (p[a] > p[b]) swap(a, b);
        p[a] += p[b];
        p[b] = a;
        return true;
    }
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of vertices
    int N = inf.readInt(1, 100000, "N");
    inf.readEoln();

    // Prepare DSU for cycle and connectivity checks
    DSU dsu(N);
    // Track seen edges to forbid duplicates
    set<pair<int,int>> seen;

    // Read edges
    for (int i = 0; i < N - 1; i++) {
        int A = inf.readInt(1, N, "A_i");
        inf.readSpace();
        int B = inf.readInt(1, N, "B_i");
        inf.readSpace();
        int W = inf.readInt(0, 1000, "W_i");
        inf.readEoln();

        // No loops
        ensuref(A != B,
                "Loop detected at edge index %d: (%d, %d)", i, A, B);

        // No multiple edges
        int u = min(A, B), v = max(A, B);
        ensuref(!seen.count({u, v}),
                "Multiple edges detected at edge index %d: (%d, %d)", i, A, B);
        seen.insert({u, v});

        // No cycles
        bool merged = dsu.unite(A, B);
        ensuref(merged,
                "Cycle detected when adding edge index %d: (%d, %d)", i, A, B);
    }

    // Check connectivity: after N-1 edges with no cycle, graph must be connected
    int comps = 0;
    for (int i = 1; i <= N; i++) {
        if (dsu.find(i) == i) comps++;
    }
    ensuref(comps == 1,
            "The graph is disconnected: %d components", comps);

    inf.readEof();
    return 0;
}
