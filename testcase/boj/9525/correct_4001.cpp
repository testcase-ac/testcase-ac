#include <bits/stdc++.h>
using namespace std;
typedef int ll;
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
int n, R, C;
char arr[100][101];
int rownum[100][100], colnum[100][100];
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	cin >> n;
	for(int i=0; i<n; i++) {
		cin >> arr[i];
	}
	for(int t=0; t<n; t++) {
		for(int i=0, j=0; i<n; i=j) {
			while(j < n && arr[t][i] == arr[t][j])
				j++;
			if(arr[t][i] == 'X') continue;
			for(int k=i; k<j; k++)
				rownum[t][k] = R;
			R++;
		}
		for(int i=0, j=0; i<n; i=j) {
			while(j < n && arr[i][t] == arr[j][t])
				j++;
			if(arr[i][t] == 'X') continue;
			for(int k=i; k<j; k++)
				colnum[k][t] = C;
			C++;
		}
	}
	Dinic dinic(R+C+2);
	for(int i=0; i<R; i++) {
		dinic.AddEdge(R+C, i, 1);
	}
	for(int i=0; i<C; i++) {
		dinic.AddEdge(R+i, R+C+1, 1);
	}
	for(int i=0; i<n; i++) {
		for(int j=0; j<n; j++) {
			if(arr[i][j] == 'X') continue;
			dinic.AddEdge(rownum[i][j], R+colnum[i][j], 1);
		}
	}
	cout << dinic.MaxFlow(R+C, R+C+1);
}
