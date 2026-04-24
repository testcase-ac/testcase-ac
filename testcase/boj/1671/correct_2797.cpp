#include <bits/stdc++.h>
using namespace std;
#define ll long long

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

int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	Dinic dinic(2*n+2);
	// source: 0, eating: [1,n], eaten: [n+1,2n], sink: 2n+1
	for(int i=1; i<=n; i++) {
		dinic.AddEdge(0,i,2);
	}
	for(int i=n+1; i<=2*n; i++) {
		dinic.AddEdge(i,2*n+1,1);
	}
	int arr[n][3] = {};
	for(int i=0; i<n; i++)
		for(int j=0; j<3; j++)
			cin >> arr[i][j];
	for(int i=0; i<n; i++) {
		for(int j=0; j<n; j++) {
			if(i == j) continue;
			if(arr[i][0] == arr[j][0] && arr[i][1] == arr[j][1] && arr[i][2] == arr[j][2]) {
				if(i < j) dinic.AddEdge(1+j,n+1+i,1);
			} else if(arr[i][0] <= arr[j][0] && arr[i][1] <= arr[j][1] && arr[i][2] <= arr[j][2]) {
				dinic.AddEdge(1+j,n+1+i,1);
			}
		}
	}
	int mx = dinic.MaxFlow(0,2*n+1);
	cout << (n-mx);
}
