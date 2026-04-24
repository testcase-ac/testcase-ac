#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

struct DSU {
    vector<int> p, r;
    DSU(int n): p(n+1), r(n+1, 0) {
        for (int i = 0; i <= n; i++) p[i] = i;
    }
    int find(int x) {
        while (p[x] != x) {
            p[x] = p[p[x]];
            x = p[x];
        }
        return x;
    }
    void unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return;
        if (r[a] < r[b]) {
            p[a] = b;
        } else if (r[b] < r[a]) {
            p[b] = a;
        } else {
            p[b] = a;
            r[a]++;
        }
    }
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read first line: N M s e
    int N = inf.readInt(2, 300000, "N");
    inf.readSpace();
    int M = inf.readInt(1, 600000, "M");
    inf.readSpace();
    int s = inf.readInt(1, N, "s");
    inf.readSpace();
    int e = inf.readInt(1, N, "e");
    inf.readEoln();
    ensuref(s != e, "Start and end vertices must differ: s=%d, e=%d", s, e);

    // Prepare DSU for connectivity check
    DSU dsu(N);

    // Read edges
    for (int i = 1; i <= M; i++) {
        int u = inf.readInt(1, N, "u_i");
        inf.readSpace();
        int v = inf.readInt(1, N, "v_i");
        inf.readSpace();
        int c = inf.readInt(0, 1, "c_i");
        inf.readEoln();

        ensuref(u != v, "Loop detected at edge %d: (%d, %d)", i, u, v);
        // Undirected edge: union for connectivity
        dsu.unite(u, v);
    }

    // Ensure there is a path from s to e
    ensuref(dsu.find(s) == dsu.find(e),
            "No path between s=%d and e=%d", s, e);

    inf.readEof();
    return 0;
}
