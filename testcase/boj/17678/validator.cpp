#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

struct DSU {
    int n;
    vector<int> p, r;
    DSU(int n = 0) { init(n); }
    void init(int n_) {
        n = n_;
        p.resize(n+1);
        r.assign(n+1, 0);
        for (int i = 1; i <= n; ++i) p[i] = i;
    }
    int findp(int x) {
        if (p[x] == x) return x;
        return p[x] = findp(p[x]);
    }
    void unite(int a, int b) {
        a = findp(a); b = findp(b);
        if (a == b) return;
        if (r[a] < r[b]) swap(a,b);
        p[b] = a;
        if (r[a] == r[b]) ++r[a];
    }
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int MAXN = 500000;

    int N = inf.readInt(1, MAXN, "N");
    inf.readSpace();
    int K = inf.readInt(1, N, "K");
    inf.readEoln();

    vector<pair<int,int>> edges;
    edges.reserve(max(0, N-1));

    for (int i = 0; i < N-1; ++i) {
        int a = inf.readInt(1, N, "A_i");
        inf.readSpace();
        int b = inf.readInt(1, N, "B_i");
        inf.readEoln();
        ensuref(a != b, "Self-loop edge at index %d: (%d, %d)", i+1, a, b);
        edges.push_back({a,b});
    }

    vector<int> S(N+1);
    vector<int> cntState(K+1, 0);
    for (int j = 1; j <= N; ++j) {
        S[j] = inf.readInt(1, K, "S_j");
        inf.readEoln();
        cntState[S[j]]++;
    }

    // Check every state has at least one city
    for (int k = 1; k <= K; ++k) {
        ensuref(cntState[k] > 0, "State %d has no city", k);
    }

    // Check that the graph is connected and is a tree (N nodes, N-1 edges, no multiple edges)
    {
        DSU dsu(N);
        // detect multiple edges using unordered_set of long long key
        unordered_set<long long> seen;
        seen.reserve(edges.size() * 2 + 1);
        const long long SHIFT = (long long)N + 1;
        for (int i = 0; i < (int)edges.size(); ++i) {
            int a = edges[i].first;
            int b = edges[i].second;
            int x = min(a,b);
            int y = max(a,b);
            long long key = (long long)x * SHIFT + y;
            ensuref(seen.insert(key).second,
                    "Multiple edge detected at index %d: (%d, %d)", i+1, a, b);
            dsu.unite(a,b);
        }
        int root = dsu.findp(1);
        for (int v = 2; v <= N; ++v) {
            ensuref(dsu.findp(v) == root,
                    "Graph is not connected: node %d not connected to node 1", v);
        }
    }

    inf.readEof();
}
