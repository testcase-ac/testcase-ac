#include "testlib.h"
#include <vector>
#include <set>
using namespace std;

struct DSU {
    int n;
    vector<int> p, rnk;
    DSU(int n = 0) { init(n); }
    void init(int n_) {
        n = n_;
        p.resize(n+1);
        rnk.assign(n+1, 0);
        for (int i = 1; i <= n; ++i) p[i] = i;
    }
    int find(int x) {
        if (p[x] == x) return x;
        return p[x] = find(p[x]);
    }
    bool unite(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) return false;
        if (rnk[a] < rnk[b]) swap(a,b);
        p[b] = a;
        if (rnk[a] == rnk[b]) ++rnk[a];
        return true;
    }
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int MAX_N = 100000;
    const int MAX_Q = 100000;
    const long long MAX_C = 1000000000LL;

    int N = inf.readInt(1, MAX_N, "N");
    inf.readSpace();
    int Q = inf.readInt(1, MAX_Q, "Q");
    inf.readEoln();

    // Read tree edges
    vector<pair<int,int>> edges;
    edges.reserve(N - 1);
    DSU dsu(N);

    for (int i = 0; i < N - 1; ++i) {
        int a = inf.readInt(1, N, "a_i");
        inf.readSpace();
        int b = inf.readInt(1, N, "b_i");
        inf.readSpace();
        long long c = inf.readLong(1LL, MAX_C, "c_i");
        inf.readEoln();

        ensuref(a != b, "Self-loop detected at edge index %d: (%d, %d)", i, a, b);
        edges.push_back({a, b});

        // Union-find for connectivity / acyclicity
        bool merged = dsu.unite(a, b);
        // If we ever cannot merge, that would indicate a cycle with <= N-1 edges,
        // but in a simple undirected graph, N-1 edges can only make at most one tree.
        // However, we still check explicitly:
        ensuref(merged, "Cycle detected when adding edge index %d: (%d, %d)", i, a, b);
    }

    // Check that graph is connected (i.e., all vertices share same representative)
    int root = dsu.find(1);
    for (int v = 2; v <= N; ++v) {
        ensuref(dsu.find(v) == root,
                "Graph is not connected: vertex %d is in a different component", v);
    }

    // Read queries
    for (int k = 0; k < Q; ++k) {
        int L = inf.readInt(1, N, "l_k");
        inf.readSpace();
        int R = inf.readInt(1, N, "r_k");
        inf.readEoln();
        ensuref(L <= R, "Query index %d has l_k > r_k: (%d, %d)", k, L, R);
    }

    inf.readEof();
}
