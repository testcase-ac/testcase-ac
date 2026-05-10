#include "testlib.h"
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

// DSU for connectivity check
struct DSU {
    vector<int> p;
    DSU(int n) : p(n+1) {
        for (int i = 1; i <= n; ++i) p[i] = i;
    }
    int find(int x) {
        return p[x] == x ? x : p[x] = find(p[x]);
    }
    void unite(int x, int y) {
        p[find(x)] = find(y);
    }
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read N, P
    int N = inf.readInt(5, 10000, "N");
    inf.readSpace();
    int P = inf.readInt(N-1, 100000, "P");
    inf.readEoln();

    // 2. Read C_i (country costs)
    vector<int> C(N+1); // 1-based
    for (int i = 1; i <= N; ++i) {
        C[i] = inf.readInt(1, 1000, "C_i");
        if (i < N) inf.readEoln();
        else inf.readEoln();
    }

    // 3. Read edges, check constraints
    set<pair<int,int>> edges;
    DSU dsu(N);
    for (int i = 0; i < P; ++i) {
        int S = inf.readInt(1, N, "S_j");
        inf.readSpace();
        int E = inf.readInt(1, N, "E_j");
        inf.readSpace();
        int L = inf.readInt(0, 1000, "L_j");
        inf.readEoln();

        ensuref(S != E, "Edge %d: S_j == E_j (%d)", i+1, S);
        pair<int,int> edge = S < E ? make_pair(S,E) : make_pair(E,S);
        ensuref(edges.count(edge) == 0, "Multiple edge between %d and %d at edge %d", S, E, i+1);
        edges.insert(edge);

        dsu.unite(S, E);
    }

    // 4. Check connectivity
    int root = dsu.find(1);
    for (int i = 2; i <= N; ++i) {
        ensuref(dsu.find(i) == root, "Graph is not connected: node %d is not connected to node 1", i);
    }

    inf.readEof();
}
