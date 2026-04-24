#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ldb long double
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
struct Point{
	ll x, y;
	Point operator-(Point a) {
		return {x-a.x,y-a.y};
	}
	bool operator==(Point a) {
		return tie(x,y) == tie(a.x,a.y);
	}
	ll dist() {
		return x*x+y*y;
	}
};
ll cross(Point p, Point q) {
	return p.x*q.y-p.y*q.x;
}
int ccw(Point A, Point B, Point C) {
	ll c = cross(B-A, C-B);
	if(c > 0) return 1; // ccw
	else if(c < 0) return -1; // cw
	else return 0; // colinear
}

int lieon(Point a, Point b, Point x) { // 0:NO 1:YES, inbetween 2:YES, at endpt
	if(ccw(a,b,x)) return 0;
	if(a == x || b == x) return 2;
	return min(a.x,b.x) <= x.x && x.x <= max(a.x,b.x) 
		&& min(a.y,b.y) <= x.y && x.y <= max(a.y,b.y);
}
int intersect(Point A, Point B, Point C, Point D) {
	/*
	0: Does not intersect.
	1: Is or is not equal straight line and intersect at exactly one point.
	2: Is equal straight line, and intersect at infinitely many point.
	*/
	ll c1 = ccw(A,B,C), c2 = ccw(A,B,D), c3 = ccw(C,D,A), c4 = ccw(C,D,B);
	if(!c1 && !c2 && !c3 && !c4) {
		if(lieon(A,B,C)==1 || lieon(A,B,D) == 1 || lieon(C,D,A) == 1) return 2;
		// if only need intersection, above line is enough
		if(A == C) return ((D-A).dist() < (D-B).dist()) ? 1 : 2;
		if(A == D) return ((C-A).dist() < (C-B).dist()) ? 1 : 2;
		if(B == C) return ((D-A).dist() > (D-B).dist()) ? 1 : 2;
		if(B == D) return ((C-A).dist() > (C-B).dist()) ? 1 : 2;
		return 0;
	} else {
		return c1 != c2 && c3 != c4;
	}
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n, K, h, m;
	cin >> n >> K >> h >> m;
	Point wall[n], hole[h], mice[m];
	for(int i=0; i<n; i++)
		cin >> wall[i].x >> wall[i].y;
	for(int i=0; i<h; i++)
		cin >> hole[i].x >> hole[i].y;
	for(int i=0; i<m; i++)
		cin >> mice[i].x >> mice[i].y;
	Dinic dinic(m+h+2);
	for(int i=1; i<=m; i++) {
		dinic.AddEdge(0,i,1);
	}
	for(int i=m+1; i<=m+h; i++) {
		dinic.AddEdge(i,m+h+1,K);
	}
	for(int i=0; i<m; i++) {
		for(int j=0; j<h; j++) {
			bool ok = true;
			for(int k=0; k<n; k++) {
				if(lieon(wall[k], wall[(k+1)%n], hole[j])) continue;
				if(intersect(wall[k], wall[(k+1)%n], hole[j], mice[i])) {
					//printf("from mice %d to hole %d: not ok as at wall %d, res=%d, opt.second=%Lf\n", i, j, k, res, opt.second);
					ok = false;
					break;
				}
			}
			if(ok) {
				//printf("from mice %d to hole %d: ok!\n", i, j);
				dinic.AddEdge(1+i,1+m+j,1);
			}
		}
	}
	ll mf = dinic.MaxFlow(0,m+h+1);
	//printf("flow is %lld\n", mf);
	cout << (mf == m ? "Possible" : "Impossible");
}
