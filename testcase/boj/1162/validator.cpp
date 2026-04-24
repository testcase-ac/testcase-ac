#include "testlib.h"
#include <vector>
using namespace std;

// Disjoint Set Union for connectivity check
struct DSU {
    vector<int> p;
    DSU(int n): p(n+1) {
        for (int i = 0; i <= n; i++) p[i] = i;
    }
    int find(int x) {
        return p[x] == x ? x : (p[x] = find(p[x]));
    }
    void unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a != b) p[b] = a;
    }
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N, M, K
    int N = inf.readInt(1, 10000, "N");
    inf.readSpace();
    int M = inf.readInt(1, 50000, "M");
    inf.readSpace();
    int K = inf.readInt(1, 20, "K");
    inf.readEoln();

    DSU dsu(N);

    // Read M roads
    for (int i = 0; i < M; i++) {
        int u = inf.readInt(1, N, "u_i");
        inf.readSpace();
        int v = inf.readInt(1, N, "v_i");
        inf.readSpace();
        int t = inf.readInt(1, 1000000, "t_i");
        inf.readEoln();

        // Union for connectivity check
        dsu.unite(u, v);
    }

    // Check that city N is reachable from city 1
    ensuref(dsu.find(1) == dsu.find(N),
            "City %d is not reachable from city %d", N, 1);

    inf.readEof();
    return 0;
}
