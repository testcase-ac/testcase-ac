#include "testlib.h"
#include <vector>
#include <numeric>
using namespace std;

struct DSU {
    vector<int> p;
    DSU(int n): p(n+1) { iota(p.begin(), p.end(), 0); }
    int find(int x) {
        return p[x] == x ? x : p[x] = find(p[x]);
    }
    void unite(int a, int b) {
        a = find(a); b = find(b);
        if (a != b) p[b] = a;
    }
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N, M
    int N = inf.readInt(1, 1000, "N");
    inf.readSpace();
    // Maximum possible undirected edges without loops is N*(N-1)/2
    int maxM = N * (N - 1) / 2;
    int M = inf.readInt(0, maxM, "M");
    inf.readEoln();

    DSU dsu(N);
    for (int i = 1; i <= M; i++) {
        int A = inf.readInt(1, N, "A_i");
        inf.readSpace();
        int B = inf.readInt(1, N, "B_i");
        inf.readSpace();
        int C = inf.readInt(1, 10, "C_i");
        inf.readEoln();

        ensuref(A != B,
                "Loop detected at edge index %d: (%d, %d)", i, A, B);

        // unite for connectivity check
        dsu.unite(A, B);
    }

    // Check connectivity: every node must be reachable from node 1
    for (int v = 1; v <= N; v++) {
        ensuref(dsu.find(v) == dsu.find(1),
                "Graph is disconnected: node %d is unreachable from node 1", v);
    }

    inf.readEof();
    return 0;
}
