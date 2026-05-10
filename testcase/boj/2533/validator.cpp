#include "testlib.h"
#include <vector>
#include <set>
using namespace std;

struct DSU {
    vector<int> p, r;
    DSU(int n): p(n+1), r(n+1, 0) {
        for (int i = 0; i <= n; i++) p[i] = i;
    }
    int find(int x) {
        while (p[x] != x) {
            x = p[x];
        }
        return x;
    }
    bool unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return false;
        if (r[a] < r[b]) {
            p[a] = b;
        } else if (r[b] < r[a]) {
            p[b] = a;
        } else {
            p[b] = a;
            r[a]++;
        }
        return true;
    }
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of vertices
    int N = inf.readInt(2, 1000000, "N");
    inf.readEoln();

    // A tree on N nodes must have exactly N-1 edges
    int M = N - 1;
    DSU dsu(N);
    set<pair<int,int>> edges;
    
    for (int i = 0; i < M; i++) {
        int u = inf.readInt(1, N, "u_i");
        inf.readSpace();
        int v = inf.readInt(1, N, "v_i");
        inf.readEoln();

        // No self-loops
        ensuref(u != v, "Loop detected at edge index %d: (%d, %d)", i, u, v);

        // Check multiple edges
        int a = min(u, v), b = max(u, v);
        pair<int,int> e = make_pair(a, b);
        ensuref(!edges.count(e),
                "Multiple edges detected at edge index %d: (%d, %d)", i, u, v);
        edges.insert(e);

        // Check cycles
        bool merged = dsu.unite(u, v);
        ensuref(merged,
                "Cycle detected at edge index %d: (%d, %d)", i, u, v);
    }

    // No extra lines
    inf.readEof();
    return 0;
}
