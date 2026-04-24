#include <bits/stdc++.h>
using namespace std;
#define int long long
// Dinic max-flow implementation adapted from Stanford ACM ICPC notebook.
// Upstream: https://github.com/jaehyunp/stanfordacm/blob/master/code/Dinic.cc
// Copyright (c) 2018 Jaehyun Park
// Licensed under the MIT License; see https://github.com/jaehyunp/stanfordacm/blob/master/LICENSE
// and this repository's LICENSE file for the MIT permission notice.
struct Edge {
    int u, v;
    int cap, flow;
    Edge() {}
    Edge(int u, int v, int cap): u(u), v(v), cap(cap), flow(0) {}
};

struct Dinic {
    int N;
    vector<Edge> E;
    vector<vector<int>> g;
    vector<int> d, pt;
    
    Dinic(int N): N(N), E(0), g(N), d(N), pt(N) {}

    void AddEdge(int u, int v, int cap) {
        if (u != v) {
            E.emplace_back(u, v, cap);
            g[u].emplace_back(E.size() - 1);
            E.emplace_back(v, u, 0);
            g[v].emplace_back(E.size() - 1);
        }
    }

    bool BFS(int S, int T) {
        queue<int> q({S});
        fill(d.begin(), d.end(), N + 1);
        d[S] = 0;
        while(!q.empty()) {
            int u = q.front(); q.pop();
            if (u == T) break;
            for (int k: g[u]) {
                Edge &e = E[k];
                if (e.flow < e.cap && d[e.v] > d[e.u] + 1) {
                    d[e.v] = d[e.u] + 1;
                    q.emplace(e.v);
                }
            }
        }
        return d[T] != N + 1;
    }

    int DFS(int u, int T, int flow = -1) {
        if (u == T || flow == 0) return flow;
        for (int &i = pt[u]; i < g[u].size(); ++i) {
            Edge &e = E[g[u][i]];
            Edge &oe = E[g[u][i]^1];
            if (d[e.v] == d[e.u] + 1) {
                int amt = e.cap - e.flow;
                if (flow != -1 && amt > flow) amt = flow;
                if (int pushed = DFS(e.v, T, amt)) {
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
        while (BFS(S, T)) {
            fill(pt.begin(), pt.end(), 0);
            while (int flow = DFS(S, T))
                total += flow;
        }
        return total;
    }
};
struct info {
    int idx;
    bool is_dog;
};
info read() {
    string s;
    cin >> s;
    if (s[0] == 'D') {
        return {stoi(s.substr(1))-1, true};
    } else {
        return {stoi(s.substr(1))-1, false};
    }
}
int solve() {
    int C, D, V;
    cin >> C >> D >> V;
    vector<pair<info, info>> edge(V);
    for (int i = 0; i < V; i++) {
        info a = read();
        info b = read();
        edge[i] = {a, b};
        // printf("emplace %d %d -> %d %d\n", a.is_dog, a.idx, b.is_dog, b.idx );
    }
    Dinic dinic(V + 2);
    const int source = V, sink = V + 1;
    for (int i = 0; i < V; i++) {
        if(edge[i].first.is_dog) {
            dinic.AddEdge(source, i, 1);
        } else {
            dinic.AddEdge(i, sink, 1);
        }
    }
    for (int i = 0; i < V; i++) {
        for (int j = i + 1; j < V; j++) {
            if(edge[i].first.is_dog == edge[j].first.is_dog) {
                // printf("continue %d %d\n", i, j);
                continue;
            }

            if (edge[i].first.idx == edge[j].second.idx || edge[i].second.idx == edge[j].first.idx) {
                if(edge[i].first.is_dog) {
                    // printf("add edge %d %d\n", i, j);
                    dinic.AddEdge(i, j, 1);
                }
                else {
                    // printf("add edge %d %d\n", j, i);
                    dinic.AddEdge(j, i, 1);
                }
            }
        }
    }
    return V - dinic.MaxFlow(source, sink);
}
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int T;
    cin >> T;
    while(T--) {
        cout << solve() << '\n';
    }
}
