#include "testlib.h"
#include <vector>
#include <set>
#include <numeric>
using namespace std;

struct DSU {
    vector<int> p;
    DSU(int n): p(n+1) { iota(p.begin(), p.end(), 0); }
    int find(int x) {
        return p[x] == x ? x : (p[x] = find(p[x]));
    }
    bool unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return false;
        p[a] = b;
        return true;
    }
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and K
    int N = inf.readInt(1, 100000, "N");
    inf.readSpace();
    int K = inf.readInt(0, N, "K");
    inf.readEoln();

    // Validate edges: must form a tree (N-1 edges, no loops, no multi-edges, no cycles)
    DSU dsu(N);
    set<pair<int,int>> seen;
    for (int i = 0; i < N-1; i++) {
        int x = inf.readInt(1, N, "x_i");
        inf.readSpace();
        int y = inf.readInt(1, N, "y_i");
        inf.readEoln();

        // No self-loop
        ensuref(x != y,
                "Loop detected at edge index %d: (%d, %d)", i, x, y);

        // Normalize edge for duplicate check
        int a = min(x, y), b = max(x, y);

        // No multiple edges
        ensuref(!seen.count({a, b}),
                "Multiple edges detected at edge index %d: (%d, %d)", i, x, y);
        seen.insert({a, b});

        // No cycles
        bool merged = dsu.unite(x, y);
        ensuref(merged,
                "Cycle detected at edge index %d: (%d, %d)", i, x, y);
    }

    // Read pre-colored barns, ensure no barn is painted twice
    vector<char> painted(N+1, false);
    for (int i = 0; i < K; i++) {
        int b = inf.readInt(1, N, "b_i");
        inf.readSpace();
        int c = inf.readInt(1, 3, "c_i");
        inf.readEoln();

        ensuref(!painted[b],
                "Barn %d painted multiple times", b);
        painted[b] = true;
    }

    // No extra content
    inf.readEof();
    return 0;
}
