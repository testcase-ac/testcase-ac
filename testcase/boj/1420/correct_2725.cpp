#include <bits/stdc++.h>
using namespace std;
char arr[100][101];
bool mark[100][101];
int str, stc, edr, edc, dr[] = {1,-1,0,0}, dc[] = {0,0,1,-1}, R, C;
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
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	cin >> R >> C;
	for(int i=0; i<R; i++) {
		cin >> arr[i];
		for(int j=0; j<C; j++) {
			if(arr[i][j] == 'K') {
				str = i;
				stc = j;
				arr[i][j] = '.';
			} else if(arr[i][j] == 'H') {
				edr = i;
				edc = j;
				arr[i][j] = '.';
			}
		}
	}
	if((abs(str-edr) == 0 && abs(stc-edc) == 1) || (abs(str-edr) == 1 && abs(stc-edc) == 0))
		return !(cout << -1);
	Dinic dinic(2*R*C);
    for(int r=0; r<R; r++) {
        for(int c=0; c<C; c++) {
            if(arr[r][c] == '#') continue;
            dinic.AddEdge(r*C+c, R*C+r*C+c, 1);
            for(int t=0; t<4; t++) {
                int tr = r+dr[t], tc = c+dc[t];
                if(!(0<=tr&&tr<R&&0<=tc&&tc<C) || arr[tr][tc] == '#') continue;
                dinic.AddEdge(R*C+r*C+c, tr*C+tc, 1000000);
            }
        }
    }
	cout << dinic.MaxFlow(R*C+str*C+stc, edr*C+edc);
}
