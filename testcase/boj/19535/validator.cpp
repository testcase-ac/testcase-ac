#include "testlib.h"
#include <vector>
#include <unordered_set>
#include <cstdint>
using namespace std;

struct DSU {
    vector<int> p, r;
    DSU(int n): p(n+1), r(n+1,0) {
        for(int i = 1; i <= n; i++) p[i] = i;
    }
    int find(int x) {
        if (p[x] == x) return x;
        return p[x] = find(p[x]);
    }
    bool unite(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) return false;
        if (r[a] < r[b]) swap(a,b);
        p[b] = a;
        if (r[a] == r[b]) r[a]++;
        return true;
    }
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(4, 300000, "N");
    inf.readEoln();

    int M = N - 1;
    DSU dsu(N);
    unordered_set<uint64_t> seen;
    seen.reserve(M * 2);

    for (int i = 1; i <= M; i++) {
        int u = inf.readInt(1, N, "u_i");
        inf.readSpace();
        int v = inf.readInt(1, N, "v_i");
        inf.readEoln();

        // No self-loops
        ensuref(u != v,
                "Loop detected at edge index %d: self-loop at vertex %d", i, u);

        // Check multiple edges (undirected)
        int a = min(u, v), b = max(u, v);
        uint64_t key = (uint64_t(a) << 32) | uint64_t(b);
        ensuref(!seen.count(key),
                "Multiple edges detected at edge index %d: (%d, %d)", i, u, v);
        seen.insert(key);

        // Check for cycles (should be a tree)
        bool merged = dsu.unite(u, v);
        ensuref(merged,
                "Cycle detected at edge index %d: adding edge (%d, %d) forms a cycle",
                i, u, v);
    }

    // Check connectivity: exactly one component
    int root0 = dsu.find(1);
    for (int i = 2; i <= N; i++) {
        ensuref(dsu.find(i) == root0,
                "Graph is not connected: vertex %d is in a different component", i);
    }

    inf.readEof();
    return 0;
}
