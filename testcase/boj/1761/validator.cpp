#include "testlib.h"
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

struct DSU {
    vector<int> p, r;
    DSU(int n): p(n+1), r(n+1, 0) {
        for (int i = 1; i <= n; i++) p[i] = i;
    }
    int find(int x) {
        return p[x] == x ? x : (p[x] = find(p[x]));
    }
    bool unite(int x, int y) {
        x = find(x); y = find(y);
        if (x == y) return false;
        if (r[x] < r[y]) swap(x, y);
        p[y] = x;
        if (r[x] == r[y]) r[x]++;
        return true;
    }
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of nodes
    int N = inf.readInt(2, 40000, "N");
    inf.readEoln();

    // Prepare DSU and edge set
    DSU dsu(N);
    set<pair<int,int>> seen;
    int unions = 0;

    // Read tree edges
    for (int i = 1; i <= N-1; i++) {
        int u = inf.readInt(1, N, "u_i");
        inf.readSpace();
        int v = inf.readInt(1, N, "v_i");
        inf.readSpace();
        int w = inf.readInt(1, 10000, "w_i");
        inf.readEoln();

        ensuref(u != v, "Loop detected at edge %d: (%d, %d)", i, u, v);

        int a = min(u, v), b = max(u, v);
        pair<int,int> e = {a, b};
        ensuref(!seen.count(e),
                "Multiple edges detected at edge %d: (%d, %d)", i, u, v);
        seen.insert(e);

        // Check for cycles
        bool merged = dsu.unite(u, v);
        ensuref(merged, "Cycle detected at edge %d: (%d, %d)", i, u, v);
        unions++;
    }
    // After N-1 edges without cycle, graph is a tree
    ensuref(unions == N-1, "Invalid number of successful unions: %d (expected %d)",
            unions, N-1);

    // Read number of queries
    int M = inf.readInt(1, 10000, "M");
    inf.readEoln();

    // Read queries
    for (int i = 1; i <= M; i++) {
        int x = inf.readInt(1, N, "x_i");
        inf.readSpace();
        int y = inf.readInt(1, N, "y_i");
        inf.readEoln();
        // queries can be same node; distance is then zero
    }

    inf.readEof();
    return 0;
}
