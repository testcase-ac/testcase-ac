#include "testlib.h"
#include <vector>
using namespace std;

struct DSU {
    vector<int> p, r;
    DSU(int n): p(n+1), r(n+1, 0) {
        for (int i = 1; i <= n; i++) p[i] = i;
    }
    int find(int x) {
        return p[x] == x ? x : p[x] = find(p[x]);
    }
    bool unite(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) return false;
        if (r[a] < r[b]) p[a] = b;
        else if (r[b] < r[a]) p[b] = a;
        else { p[b] = a; r[a]++; }
        return true;
    }
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of vertices
    int N = inf.readInt(2, 100000, "N");
    inf.readEoln();

    // Read and validate tree edges
    DSU dsu(N);
    for (int i = 1; i <= N-1; i++) {
        int u = inf.readInt(1, N, "u");
        inf.readSpace();
        int v = inf.readInt(1, N, "v");
        inf.readEoln();

        // No self-loops
        ensuref(u != v,
                "Loop detected at edge %d: (%d, %d)", i, u, v);

        // No cycles / no multiple edges
        if (!dsu.unite(u, v)) {
            ensuref(false,
                    "Cycle detected at edge %d: (%d, %d)", i, u, v);
        }
    }

    // Number of queries
    int M = inf.readInt(1, 100000, "M");
    inf.readEoln();

    // Read and validate queries
    for (int i = 1; i <= M; i++) {
        int type = inf.readInt(1, 2, "type");
        inf.readSpace();
        int x = inf.readInt(1, N, "node");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
