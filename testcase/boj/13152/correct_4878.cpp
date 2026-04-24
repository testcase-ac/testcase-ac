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
int n, m;
pair<int, int> edges[25000];
bool go(int mx) {
	Dinic dinic(n+m+2);
	// source: 0
	// edge: [1, m]
	// node: [m+1, m+n]
	// sink: m+n+1
	for(int i=1; i<=m; i++) {
		auto [a, b] = edges[i-1];
		dinic.AddEdge(0, i, 1);
		dinic.AddEdge(i, m+a, 1);
		dinic.AddEdge(i, m+b, 1);
	}
	for(int i=1; i<=n; i++) {
		dinic.AddEdge(m+i, m+n+1, mx);
	}
	return dinic.MaxFlow(0, m+n+1) == m;
}
int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	cin >> n >> m;
	for(int i=0; i<m; i++) {
		cin >> edges[i].first >> edges[i].second;
	}
	int l = 0, r = n;
	while(l < r) {
		int mid = (l+r)/2;
		if(go(mid)) {
			r = mid;
		} else {
			l = mid+1;
		}
	}
	cout << l;
}
