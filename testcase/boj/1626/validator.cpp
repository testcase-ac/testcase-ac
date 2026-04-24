#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll INF64 = (ll)4e18;

struct DSU {
    int n;
    vector<int> p, r;
    DSU(int _n): n(_n), p(n+1), r(n+1,0) {
        iota(p.begin(), p.end(), 0);
    }
    int find(int x) {
        return p[x]==x ? x : p[x] = find(p[x]);
    }
    bool unite(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) return false;
        if (r[a] < r[b]) swap(a,b);
        p[b] = a;
        if (r[a] == r[b]) r[a]++;
        return true;
    }
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);
    // Single test case
    int V = inf.readInt(1, 50000, "V");
    inf.readSpace();
    int E = inf.readInt(1, 200000, "E");
    inf.readEoln();
    struct Edge { int u,v; int w; bool used; };
    vector<Edge> edges;
    edges.reserve(E);
    for (int i = 0; i < E; i++) {
        int u = inf.readInt(1, V, "u_i");
        inf.readSpace();
        int v = inf.readInt(1, V, "v_i");
        inf.readSpace();
        int w = inf.readInt(0, 100000, "w_i");
        inf.readEoln();
        ensuref(u != v, "Loop detected on edge %d: %d-%d", i, u, v);
        edges.push_back({u,v,w,false});
    }
    // Compute MST by Kruskal
    vector<int> idx(E);
    iota(idx.begin(), idx.end(), 0);
    sort(idx.begin(), idx.end(), [&](int a, int b){
        return edges[a].w < edges[b].w;
    });
    DSU dsu(V);
    ll mstSum = 0;
    int usedEdges = 0;
    for (int id : idx) {
        auto &e = edges[id];
        if (dsu.unite(e.u, e.v)) {
            e.used = true;
            mstSum += e.w;
            usedEdges++;
            if (usedEdges == V-1) break;
        }
    }
    // If MST exists (graph connected), build for second MST
    ll secondBest = INF64;
    if (usedEdges == V-1 && V > 1) {
        // build tree adjacency
        vector<vector<pair<int,int>>> adj(V+1);
        for (auto &e : edges) if (e.used) {
            adj[e.u].push_back({e.v, e.w});
            adj[e.v].push_back({e.u, e.w});
        }
        // prepare LCA
        int LOG = 1;
        while ((1<<LOG) <= V) LOG++;
        vector<int> depth(V+1, -1);
        vector<vector<int>> parent(LOG, vector<int>(V+1, -1));
        vector<vector<int>> maxW(LOG, vector<int>(V+1, 0));
        // BFS from 1
        queue<int> q;
        depth[1] = 0;
        q.push(1);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (auto &pr : adj[u]) {
                int v = pr.first, w = pr.second;
                if (depth[v] == -1) {
                    depth[v] = depth[u] + 1;
                    parent[0][v] = u;
                    maxW[0][v] = w;
                    q.push(v);
                }
            }
        }
        // lift
        for (int k = 1; k < LOG; k++) {
            for (int v = 1; v <= V; v++) {
                int p = parent[k-1][v];
                if (p < 0) {
                    parent[k][v] = -1;
                    maxW[k][v] = maxW[k-1][v];
                } else {
                    parent[k][v] = parent[k-1][p];
                    maxW[k][v] = max(maxW[k-1][v], maxW[k-1][p]);
                }
            }
        }
        // function to get max on path
        auto getMaxOnPath = [&](int u, int v) {
            int mx = 0;
            if (depth[u] < depth[v]) swap(u,v);
            int diff = depth[u] - depth[v];
            for (int k = 0; k < LOG; k++) if (diff & (1<<k)) {
                mx = max(mx, maxW[k][u]);
                u = parent[k][u];
            }
            if (u == v) return mx;
            for (int k = LOG-1; k >= 0; k--) {
                if (parent[k][u] != parent[k][v]) {
                    mx = max(mx, maxW[k][u]);
                    mx = max(mx, maxW[k][v]);
                    u = parent[k][u];
                    v = parent[k][v];
                }
            }
            // one more step
            mx = max(mx, maxW[0][u]);
            mx = max(mx, maxW[0][v]);
            return mx;
        };
        // consider every non-MST edge
        for (auto &e : edges) if (!e.used) {
            int u = e.u, v = e.v, w = e.w;
            ll mx = getMaxOnPath(u, v);
            // if replace yields spanning tree
            if (mx < w) {
                ll cand = mstSum + w - mx;
                if (cand > mstSum && cand < secondBest) {
                    secondBest = cand;
                }
            }
        }
    }
    // enforce answer bound if second MST found
    if (secondBest < INF64) {
        const ll LIM = 2147483647LL;
        ensuref(secondBest <= LIM,
                "Second MST weight %lld exceeds promised limit %lld",
                secondBest, LIM);
    }
    inf.readEof();
    return 0;
}
