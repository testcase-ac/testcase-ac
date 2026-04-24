#include "testlib.h"
#include <vector>
using namespace std;

struct DSU {
    vector<int> p, r;
    DSU(int n): p(n+1), r(n+1, 0) {
        for (int i = 1; i <= n; i++) p[i] = i;
    }
    int find(int x) {
        while (p[x] != x) {
            p[x] = p[p[x]];
            x = p[x];
        }
        return x;
    }
    bool unite(int a, int b) {
        int ra = find(a);
        int rb = find(b);
        if (ra == rb) return false;
        if (r[ra] < r[rb]) {
            p[ra] = rb;
        } else if (r[rb] < r[ra]) {
            p[rb] = ra;
        } else {
            p[rb] = ra;
            r[ra]++;
        }
        return true;
    }
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of vertices
    int N = inf.readInt(1, 1000000, "N");
    inf.readEoln();

    // Prepare DSU for cycle and connectivity checks
    DSU dsu(N);

    // There must be exactly N-1 edges
    for (int i = 1; i <= N - 1; i++) {
        int a = inf.readInt(1, N, "a");
        inf.readSpace();
        int b = inf.readInt(1, N, "b");
        inf.readEoln();

        // No loops allowed
        ensuref(a != b, "Loop detected on edge %d: (%d, %d)", i, a, b);

        // Must remain acyclic (and thus no multi-edge)
        bool merged = dsu.unite(a, b);
        ensuref(merged, "Cycle or multiple edge detected on edge %d: (%d, %d)", i, a, b);
    }

    // After N-1 edges, must be a tree: no need to explicitly check connectivity
    // (a forest with N nodes and N-1 edges without cycles is connected)

    // End of file
    inf.readEof();
    return 0;
}
