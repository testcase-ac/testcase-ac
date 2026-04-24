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
        if (r[a] < r[b]) swap(a, b);
        p[b] = a;
        if (r[a] == r[b]) r[a]++;
        return true;
    }
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // N
    int N = inf.readInt(1, 100000, "N");
    inf.readEoln();

    // A, B, C
    int A = inf.readInt(1, N, "A"); inf.readSpace();
    int B = inf.readInt(1, N, "B"); inf.readSpace();
    int C = inf.readInt(1, N, "C"); inf.readEoln();
    ensuref(A != B && A != C && B != C,
            "A, B, C must be distinct; got A=%d, B=%d, C=%d", A, B, C);

    // M
    // From degree constraint each node ≤5 and undirected => M ≤ floor(5*N/2)
    int maxM = int((5LL * N) / 2);
    int M = inf.readInt(0, maxM, "M");
    inf.readEoln();
    // For connectivity need at least N-1 edges when N>1
    if (N > 1)
        ensuref(M >= N-1, "M must be at least N-1 for connectivity; got M=%d, N=%d", M, N);

    // Prepare for checking edges
    vector<vector<int>> adj(N+1);
    vector<int> deg(N+1, 0);
    DSU dsu(N);

    // Read edges
    for (int i = 0; i < M; i++) {
        int X = inf.readInt(1, N, "X");
        inf.readSpace();
        int Y = inf.readInt(1, N, "Y");
        inf.readSpace();
        int Z = inf.readInt(1, 10000, "Z");
        inf.readEoln();

        // No loops
        ensuref(X != Y,
                "Loop detected at edge index %d: (%d, %d)", i+1, X, Y);

        // No multi-edges
        bool duplicate = false;
        for (int v : adj[X]) {
            if (v == Y) { duplicate = true; break; }
        }
        ensuref(!duplicate,
                "Multiple edges detected between %d and %d at edge index %d", X, Y, i+1);

        // Insert undirected edge
        adj[X].push_back(Y);
        adj[Y].push_back(X);

        // Degree constraint
        deg[X]++; deg[Y]++;
        ensuref(deg[X] <= 5,
                "Degree of node %d exceeds 5: %d", X, deg[X]);
        ensuref(deg[Y] <= 5,
                "Degree of node %d exceeds 5: %d", Y, deg[Y]);

        // Union for connectivity
        dsu.unite(X, Y);
    }

    // Check connectivity
    int comps = 0;
    for (int i = 1; i <= N; i++) {
        if (dsu.find(i) == i) comps++;
    }
    ensuref(comps == 1,
            "Graph is not connected; found %d components", comps);

    // Queries
    int T = inf.readInt(1, 10000, "T");
    inf.readEoln();
    for (int i = 0; i < T; i++) {
        char qname[20];
        sprintf(qname, "Q[%d]", i+1);
        inf.readInt(1, N, qname);
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
