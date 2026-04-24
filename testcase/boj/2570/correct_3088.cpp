#include <bits/stdc++.h>
using namespace std;
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
int board[100][100], up[100][100], down[100][100], n, upnxt, dnnxt;
int f(pair<int, int> pr) {
	return board[pr.first][pr.second];
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int m;
	cin >> n >> m;
	while(m--) {
		int a, b;
		cin >> a >> b;
		board[a-1][b-1] = 1;
	}
	map<int, vector<pair<int, int>>> add, sub;
	for(int i=0; i<n; i++) {
		for(int j=0; j<n; j++) {
			add[i+j].push_back({i,j});
			sub[i-j].push_back({i,j});
		}
	}
	for(auto &[t, v]: add) {
		int j = 0;
		for(int i=0; i<v.size(); i=j) {
			if(f(v[i])) {j++;continue;}
			while(j < v.size() && !f(v[j])) j++;
			for(int k=i; k<j; k++) {
				up[v[k].first][v[k].second] = upnxt;
			}
			upnxt++;
		}
	}
	for(auto &[t, v]: sub) {
		int j = 0;
		for(int i=0; i<v.size(); i=j) {
			if(f(v[i])) {j++;continue;}
			while(j < v.size() && !f(v[j])) j++;
			for(int k=i; k<j; k++) {
				down[v[k].first][v[k].second] = dnnxt;
			}
			dnnxt++;
		}
	}
	Dinic dinic(upnxt+dnnxt+2);
	int nsum = upnxt+dnnxt;
	for(int i=0; i<upnxt; i++) {
		dinic.AddEdge(nsum, i, 1);
	}
	for(int i=upnxt; i<upnxt+dnnxt; i++) {
		dinic.AddEdge(i, nsum+1, 1);
	}
	for(int i=0; i<n; i++) {
		for(int j=0; j<n; j++) {
			if(board[i][j]) continue;
			dinic.AddEdge(up[i][j], upnxt+down[i][j], 1);
		}
	}
	cout << dinic.MaxFlow(nsum, nsum+1);
}
