#include <bits/stdc++.h>
using namespace std;
typedef pair<double, double> pt;
#define x first
#define y second
typedef long long ll;
// Dinic max-flow implementation adapted from Stanford ACM ICPC notebook.
// Upstream: https://github.com/jaehyunp/stanfordacm/blob/master/code/Dinic.cc
// Copyright (c) 2018 Jaehyun Park
// Licensed under the MIT License; see https://github.com/jaehyunp/stanfordacm/blob/master/LICENSE
// and this repository's LICENSE file for the MIT permission notice.
struct Edge {
    int u, v;
    ll cap, flow;
    Edge() {}
    Edge(int u, int v, ll cap): u(u), v(v), cap(cap), flow(0) {}
};
struct Dinic {
    int N;
    vector<Edge> E;
    vector<vector<int>> g;
    vector<int> d, pt;
    
    Dinic(int N): N(N), E(0), g(N), d(N), pt(N) {}

    void AddEdge(int u, int v, ll cap) {
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

    ll DFS(int u, int T, ll flow = -1) {
        if (u == T || flow == 0) return flow;
        for (int &i = pt[u]; i < g[u].size(); ++i) {
            Edge &e = E[g[u][i]];
            Edge &oe = E[g[u][i]^1];
            if (d[e.v] == d[e.u] + 1) {
                ll amt = e.cap - e.flow;
                if (flow != -1 && amt > flow) amt = flow;
                if (ll pushed = DFS(e.v, T, amt)) {
                    e.flow += pushed;
                    oe.flow -= pushed;
                    return pushed;
                }
            }
        }
        return 0;
    }

    ll MaxFlow(int S, int T) {
        ll total = 0;
        while (BFS(S, T)) {
            fill(pt.begin(), pt.end(), 0);
            while (ll flow = DFS(S, T))
                total += flow;
        }
        return total;
    }
};
double sq(double i){return i*i;}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n, m;
    ll s, v;
	cin >> n >> m >> s >> v;
	vector<pt> rat(n), hole(m);
	Dinic dinic(n+m+2);
	for(int i=0; i<n; i++) {
		cin >> rat[i].x >> rat[i].y;
		dinic.AddEdge(n+m, i, 1);
	}
	for(int i=0; i<m; i++) {
		cin >> hole[i].x >> hole[i].y;
		dinic.AddEdge(i+n, n+m+1, 1);
	}
    for(int i=0; i<n; i++) {
        for(int j=0; j<m; j++) {
            double distsq = sq(rat[i].x-hole[j].x)+sq(rat[i].y-hole[j].y);
            if(distsq <= s*v*s*v) {
                dinic.AddEdge(i, n+j, 1);
            }
        }
    }
    cout << n - dinic.MaxFlow(n+m, n+m+1);
}
