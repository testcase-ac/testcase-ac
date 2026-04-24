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
char arr[50][51];
int num[50][50], c2p[2500][2500], nxtc, nxtp, R, C;
bool seen[50][50];
int di[] = {1,-1,0,0}, dj[] = {0,0,1,-1};
void f(int si, int sj) {
	queue<pair<int, int>> que({{si,sj}});
	memset(seen, 0, sizeof seen);
	int d = 0;
	while(que.size()) {
		int s = que.size();
		while(s--) {
			int i, j;
			tie(i,j) = que.front();
			que.pop();
			if(arr[i][j] == 'P')
				c2p[num[si][sj]][num[i][j]] = d;
			for(int t=0; t<4; t++) {
				int ti = i+di[t], tj = j+dj[t];
				if(0 <= ti && ti < R && 0 <= tj && tj < C && arr[ti][tj] != 'X' && !seen[ti][tj]) {
					seen[ti][tj] = 1;
					que.push({ti,tj});
				}
			}
		}
		d++;
	}
}
bool ok(int t) {
	Dinic dinic(nxtc+nxtp+2);
	for(int i=0; i<nxtp; i++)
		dinic.AddEdge(nxtc+i, nxtc+nxtp+1, 1);
	for(int i=0; i<nxtc; i++) {
		dinic.AddEdge(nxtc+nxtp, i, 1);
		for(int j=0; j<nxtp; j++) {
			if(c2p[i][j] <= t) {
				dinic.AddEdge(i, nxtc+j, 1);
			}
		}
	}
	return dinic.MaxFlow(nxtc+nxtp, nxtc+nxtp+1) == nxtc;
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	cin >> R >> C;
	for(int i=0; i<R; i++) {
		cin >> arr[i];
		for(int j=0; j<C; j++) {
			if(arr[i][j] == 'C')
				num[i][j] = nxtc++;
			else if(arr[i][j] == 'P')
				num[i][j] = nxtp++;
		}
	}
	if(nxtc == 0)
		return !(cout << 0);
	memset(c2p, 0x3f, sizeof c2p);
	for(int i=0; i<R; i++) {
		for(int j=0; j<C; j++) {
			if(arr[i][j] == 'C')
				f(i, j);
		}
	}
	int l = 1, r = 2501;
	while(l < r) {
		int m = (l+r)/2;
		if(ok(m)) {
			r = m;
		} else {
			l = m+1;
		}
	}
	cout << (l == 2501 ? -1 : l);
}
