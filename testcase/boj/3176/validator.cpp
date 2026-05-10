#include "testlib.h"
#include <vector>
#include <set>
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

    // Read number of cities
    int N = inf.readInt(2, 100000, "N");
    inf.readEoln();

    // Prepare to validate tree edges
    DSU dsu(N);
    set<pair<int,int>> edges;
    for (int i = 1; i <= N-1; i++) {
        int A = inf.readInt(1, N, "A_i");
        inf.readSpace();
        int B = inf.readInt(1, N, "B_i");
        inf.readSpace();
        int C = inf.readInt(1, 1000000, "C_i");
        inf.readEoln();

        // No self-loops
        ensuref(A != B, "Loop detected at edge %d: (%d, %d)", i, A, B);

        // No multiple edges
        int u = min(A, B), v = max(A, B);
        pair<int,int> e = make_pair(u, v);
        ensuref(!edges.count(e),
                "Multiple edges detected at edge %d: (%d, %d)", i, A, B);
        edges.insert(e);

        // No cycles
        bool merged = dsu.unite(A, B);
        ensuref(merged,
                "Cycle detected when adding edge %d: (%d, %d)", i, A, B);
    }

    // After adding N-1 edges, tree must be connected
    ensuref(dsu.comps == 1,
            "Graph is not connected: has %d components", dsu.comps);

    // Read number of queries
    int K = inf.readInt(1, 100000, "K");
    inf.readEoln();

    // Read queries
    for (int i = 1; i <= K; i++) {
        int D = inf.readInt(1, N, "D_i");
        inf.readSpace();
        int E = inf.readInt(1, N, "E_i");
        inf.readEoln();
        ensuref(D != E, "Query %d has identical endpoints: %d and %d",
                i, D, E);
    }

    inf.readEof();
    return 0;
}
