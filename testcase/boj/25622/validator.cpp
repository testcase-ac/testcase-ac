#include "testlib.h"
#include <vector>
using namespace std;

// Disjoint Set Union (Union-Find) with path compression and union by rank
struct DSU {
    int n;
    vector<int> p, r;
    DSU(int _n): n(_n), p(n+1), r(n+1, 0) {
        for (int i = 1; i <= n; i++) p[i] = i;
    }
    int find(int x) {
        return p[x] == x ? x : p[x] = find(p[x]);
    }
    bool unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return false;
        if (r[a] < r[b]) swap(a, b);
        p[b] = a;
        if (r[a] == r[b]) r[a]++;
        return true;
    }
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(3, 333333, "N");
    ensuref(N % 3 == 0, "N is not a multiple of 3: %d", N);
    inf.readEoln();

    // Initialize DSU for connectivity/cycle checks
    DSU dsu(N);

    // Read edges: must be exactly N-1 lines
    for (int i = 0; i < N - 1; i++) {
        int u = inf.readInt(1, N, "u_i");
        inf.readSpace();
        int v = inf.readInt(1, N, "v_i");
        inf.readEoln();

        // No self-loops
        ensuref(u != v,
                "Self-loop detected at edge index %d: (%d, %d)", i, u, v);

        // No cycles / multiple edges: union must succeed exactly N-1 times
        bool merged = dsu.unite(u, v);
        ensuref(merged,
                "Cycle or duplicate edge detected at edge index %d: (%d, %d)",
                i, u, v);
    }

    // Ensure connectivity: after N-1 successful unions, all nodes in one component
    int comps = 0;
    for (int i = 1; i <= N; i++) {
        if (dsu.find(i) == i) comps++;
    }
    ensuref(comps == 1,
            "Graph is not connected: %d components found", comps);

    // No extra data
    inf.readEof();
    return 0;
}
