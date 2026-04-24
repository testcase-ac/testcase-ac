#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MX = 3e4;
struct edge {
    int v, w;
    bool operator<(const edge &e) const {
        return w > e.w;
    }
};
vector<edge> adj[MX], par[MX];
int  dist[MX];
// Dinic max-flow implementation adapted from Stanford ACM ICPC notebook.
// Upstream: https://github.com/jaehyunp/stanfordacm/blob/master/code/Dinic.cc
// Copyright (c) 2018 Jaehyun Park
// Licensed under the MIT License; see https://github.com/jaehyunp/stanfordacm/blob/master/LICENSE
// and this repository's LICENSE file for the MIT permission notice.
struct Edge {
    int u, v, cap, flow;
    Edge() {}
    Edge(int u, int v, int cap): u(u), v(v), cap(cap), flow(0) {}
};

struct Dinic {
    int N;
    vector<Edge> E;
    vector<vector<int>> g;
    vector<int> d, pt;
    Dinic(int N): N(N), E(0), g(N), d(N), pt(N) {}

    void addEdge(int u, int v, int cap) {
        if(u != v) {
            E.push_back({u, v, cap});
            g[u].push_back(E.size() - 1);
            E.push_back({v, u, 0});
            g[v].push_back(E.size() - 1);
        }
    }
    bool bfs(int S, int T) {
        queue<int> q({S});
        fill(d.begin(), d.end(), N+1);
        d[S] = 0;
        while(q.size()) {
            int u = q.front();
            q.pop();
            if(u == T) break;
            for(int k: g[u]) {
                Edge &e = E[k];
                if(e.flow < e.cap && d[e.v] > d[e.u] + 1) {
                    d[e.v] = d[e.u] + 1;
                    q.push(e.v);
                }
            }
        }
        return d[T] != N+1;
    }

    int dfs(int u, int T, int flow=-1) {
        if(u == T || flow == 0) return flow;
        for(int &i = pt[u]; i < g[u].size(); i++) {
            Edge &e = E[g[u][i]];
            Edge &oe = E[g[u][i] ^ 1];
            if(d[e.v] == d[e.u] + 1) {
                int amt = e.cap - e.flow;
                if(flow != -1 && amt > flow)
                    amt = flow;
                if(int pushed = dfs(e.v, T, amt)) {
                    e.flow += pushed;
                    oe.flow -= pushed;
                    return pushed;
                }
            }
        }
        return 0;
    }

    int MaxFlow(int S, int T) {
        int total = 0;
        while(bfs(S, T)) {
            fill(pt.begin(), pt.end(), 0);
            while(int flow = dfs(S, T)) {
                total += flow;
            }
        }
        return total;
    }
};
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int N, M, C;
    cin >> N >> M >> C;
    for(int i=0; i<M; i++) {
        int x, y, t;
        cin >> x >> y >> t;
        adj[x].push_back({y, t});
        adj[y].push_back({x, t});
    }
    vector<int> cust(C);
    for(int i=0; i<C; i++) {
        cin >> cust[i];
    }
    memset(dist, 0x3f, sizeof dist);
    priority_queue<edge> pq;
    dist[1] = 0;
    pq.push({1, 0});
    while(pq.size()) {
        auto [u, uw] = pq.top();
        pq.pop();
        if(uw > dist[u]) continue;
        for(auto [a, w]: adj[u]) {
            if(dist[u] + w < dist[a]) {
                dist[a] = dist[u] + w;
                pq.push({a, dist[a]});
                par[a].clear();
                par[a].push_back({u, 1});
            } else if(dist[u] + w == dist[a]) {
                par[a].push_back({u, 1});
            }
        }
    }
    map<int, vector<int>> mp;
    for(int t: cust) {
        mp[dist[t]].push_back(t);
    }
    int ans = 0;
    for(auto &[d, v]: mp) {
        Dinic dinic(N+1);
        for(int t: v) {
            dinic.addEdge(0, t, 1);
        }
        for(int i=1; i<=N; i++) {
            for(auto [p, pw]: par[i]) {
                dinic.addEdge(i, p, 1);
            }
        }
        ans += dinic.MaxFlow(0, 1);
    }
    cout << ans;
}
