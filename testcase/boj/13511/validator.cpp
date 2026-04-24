#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

struct DSU {
    int n;
    vector<int> p, r;
    DSU(int _n): n(_n), p(n), r(n, 0) {
        iota(p.begin(), p.end(), 0);
    }
    int find(int x) {
        return p[x] == x ? x : p[x] = find(p[x]);
    }
    // returns true if merged, false if already in same set
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

    // Read number of nodes
    int N = inf.readInt(2, 100000, "N");
    inf.readEoln();

    DSU dsu(N+1);
    vector<vector<int>> adj(N+1);
    set<pair<int,int>> edgeSet;

    // Read tree edges
    for (int i = 0; i < N-1; i++) {
        int u = inf.readInt(1, N, "u_i");
        inf.readSpace();
        int v = inf.readInt(1, N, "v_i");
        inf.readSpace();
        int w = inf.readInt(1, 1000000, "w_i"); // cost
        inf.readEoln();

        ensuref(u != v,
                "Loop detected on edge %d: both endpoints are %d", i+1, u);
        int a = min(u, v), b = max(u, v);
        auto pr = edgeSet.insert({a, b});
        ensuref(pr.second,
                "Multiple edges detected between %d and %d on edge %d", a, b, i+1);

        bool merged = dsu.unite(u, v);
        ensuref(merged,
                "Cycle detected when adding edge %d between %d and %d", i+1, u, v);

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // Ensure connectivity: with N-1 edges and no cycles, it's a tree, but we verify
    int comps = 0;
    for (int i = 1; i <= N; i++) {
        if (dsu.find(i) == i) comps++;
    }
    ensuref(comps == 1, "Graph is not connected: %d components found", comps);

    // Build LCA structure
    const int MAXLG = 18;
    vector<array<int, MAXLG>> parent(N+1);
    vector<int> depth(N+1, -1);

    // BFS from node 1
    queue<int> q;
    depth[1] = 0;
    parent[1].fill(1);
    q.push(1);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : adj[u]) {
            if (depth[v] == -1) {
                depth[v] = depth[u] + 1;
                parent[v][0] = u;
                q.push(v);
            }
        }
    }
    // Check all reachable
    for (int i = 1; i <= N; i++) {
        ensuref(depth[i] >= 0,
                "Node %d is not connected to the tree root", i);
    }
    // Binary lifting
    for (int lg = 1; lg < MAXLG; lg++) {
        for (int i = 1; i <= N; i++) {
            parent[i][lg] = parent[ parent[i][lg-1] ][lg-1];
        }
    }

    auto getLCA = [&](int u, int v) {
        if (depth[u] < depth[v]) swap(u, v);
        int diff = depth[u] - depth[v];
        for (int k = 0; k < MAXLG; k++) {
            if (diff & (1 << k)) {
                u = parent[u][k];
            }
        }
        if (u == v) return u;
        for (int k = MAXLG-1; k >= 0; k--) {
            if (parent[u][k] != parent[v][k]) {
                u = parent[u][k];
                v = parent[v][k];
            }
        }
        return parent[u][0];
    };

    // Read queries
    int M = inf.readInt(1, 100000, "M");
    inf.readEoln();
    for (int i = 0; i < M; i++) {
        int type = inf.readInt(1, 2, "type");
        if (type == 1) {
            inf.readSpace();
            int u = inf.readInt(1, N, "u_q");
            inf.readSpace();
            int v = inf.readInt(1, N, "v_q");
            inf.readEoln();
            // no further validation for type 1
        } else {
            // type == 2
            inf.readSpace();
            int u = inf.readInt(1, N, "u_q");
            inf.readSpace();
            int v = inf.readInt(1, N, "v_q");
            inf.readSpace();
            long long k = inf.readLong(1LL, (long long)N, "k_q");
            inf.readEoln();

            int anc = getLCA(u, v);
            long long pathLen = (long long)depth[u] + depth[v] - 2LL*depth[anc] + 1LL;
            ensuref(k >= 1 && k <= pathLen,
                    "Query %d type 2: k=%lld is out of bounds for path length=%lld", 
                    i+1, k, pathLen);
        }
    }

    inf.readEof();
    return 0;
}
