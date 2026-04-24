#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

struct DSU {
    vector<int> p;
    DSU(int n): p(n+1) { iota(p.begin(), p.end(), 0); }
    int find(int x) { return p[x]==x ? x : p[x]=find(p[x]); }
    bool unite(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) return false;
        p[b] = a;
        return true;
    }
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(3, 1024, "N");
    inf.readEoln();

    // Read upper-triangular distances
    vector<vector<int>> d(N+1, vector<int>(N+1, 0));
    for (int i = 1; i <= N-1; i++) {
        for (int j = i+1; j <= N; j++) {
            int dij = inf.readInt(1, 15000, "d[i][j]");
            d[i][j] = dij;
            d[j][i] = dij;
            if (j < N) {
                inf.readSpace();
            } else {
                inf.readEoln();
            }
        }
    }

    // Build list of all pairs
    vector<tuple<int,int,int>> edges;
    edges.reserve((long long)N*(N-1)/2);
    for (int i = 1; i <= N; i++) {
        for (int j = i+1; j <= N; j++) {
            edges.emplace_back(d[i][j], i, j);
        }
    }
    sort(edges.begin(), edges.end(),
         [](auto &a, auto &b){ return get<0>(a) < get<0>(b); });

    // Kruskal to reconstruct tree
    DSU dsu(N);
    vector<vector<pair<int,int>>> adj(N+1);
    int used = 0;
    for (auto &e : edges) {
        int w = get<0>(e), u = get<1>(e), v = get<2>(e);
        if (dsu.unite(u, v)) {
            adj[u].emplace_back(v, w);
            adj[v].emplace_back(u, w);
            used++;
            if (used == N-1) break;
        }
    }
    ensuref(used == N-1, "Could not select %d edges for the tree, only %d", N-1, used);

    // Verify the reconstructed tree distances match input distances
    vector<long long> dist2(N+1);
    vector<int> vis(N+1);
    for (int src = 1; src <= N; src++) {
        // BFS/DFS to compute distances from src
        fill(dist2.begin(), dist2.end(), -1);
        queue<int> q;
        dist2[src] = 0;
        q.push(src);
        int cnt = 1;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (auto &pr : adj[u]) {
                int v = pr.first, w = pr.second;
                if (dist2[v] < 0) {
                    dist2[v] = dist2[u] + w;
                    q.push(v);
                    cnt++;
                }
            }
        }
        ensuref(cnt == N, "Tree is disconnected: only %d nodes reachable from %d", cnt, src);

        // Compare distances
        for (int j = 1; j <= N; j++) {
            long long got = dist2[j];
            int expv = d[src][j];
            ensuref(got == expv,
                    "Distance mismatch: dist[%d][%d] = %lld but expected %d",
                    src, j, got, expv);
        }
    }

    inf.readEof();
    return 0;
}
