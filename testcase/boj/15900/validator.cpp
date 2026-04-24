#include "testlib.h"
#include <vector>
#include <unordered_set>
#include <cstdint>
using namespace std;

// Disjoint Set Union with path compression and union by rank
struct DSU {
    vector<int> p, r;
    DSU(int n): p(n+1), r(n+1, 0) {
        for(int i = 1; i <= n; i++) p[i] = i;
    }
    int find(int x) {
        if (p[x] != x) p[x] = find(p[x]);
        return p[x];
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

    // Read N
    int N = inf.readInt(2, 500000, "N");
    inf.readEoln();

    // Prepare DSU and edge set
    DSU dsu(N);
    unordered_set<uint64_t> seen;
    seen.reserve((size_t)N);

    // Read edges
    for (int i = 0; i < N-1; i++) {
        int a = inf.readInt(1, N, "a_i");
        inf.readSpace();
        int b = inf.readInt(1, N, "b_i");
        inf.readEoln();

        // No loops
        ensuref(a != b,
                "Loop detected at edge index %d: (%d, %d)", i, a, b);

        // Normalize edge for duplicate detection
        int u = a < b ? a : b;
        int v = a < b ? b : a;
        // Create unique key
        uint64_t key = uint64_t(u) * (uint64_t(N) + 1) + uint64_t(v);
        // No multiple edges
        ensuref(!seen.count(key),
                "Multiple edges detected at edge index %d: (%d, %d)", i, a, b);
        seen.insert(key);

        // No cycles
        if (!dsu.unite(a, b)) {
            ensuref(false,
                    "Cycle detected at edge index %d: (%d, %d)", i, a, b);
        }
    }

    // Implicitly, N-1 edges and no cycles => connected tree

    inf.readEof();
    return 0;
}
