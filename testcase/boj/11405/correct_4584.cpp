#include <bits/stdc++.h>
using namespace std;
struct Edge{
	int u, v, w, cap, flow;
};
const int INF = 0x3f3f3f3f;
struct MCMF {
	int n;
	vector<Edge> edges;
	vector<vector<int>> adj;
	vector<int> par, dist, inque;
	MCMF(int _n) {
		n = _n;
		adj.resize(n+1);
		par.resize(n+1);
		dist.resize(n+1);
		inque.resize(n+1);
	}
	void addedge(int u, int v, int w, int cap) {
		adj[u].push_back(edges.size());
		edges.push_back({u, v, w, cap, 0});
		adj[v].push_back(edges.size());
		edges.push_back({v, u, -w, cap, cap});
	}
	void spfa(int src) {
		fill(par.begin(), par.end(), -1);
		fill(dist.begin(), dist.end(), INF);
		fill(inque.begin(), inque.end(), 0);
		dist[src] = 0;
		queue<int> que({src});
		while(que.size()) {
			int q = que.front();
			que.pop();
			inque[q] = 0;
			for(int i: adj[q]) {
				Edge& e = edges[i];
				if(e.flow < e.cap && dist[e.v] > dist[e.u]+e.w) {
					dist[e.v] = dist[e.u]+e.w;
					par[e.v] = i;
					if(!inque[e.v]) {
						inque[e.v] = 1;
						que.push(e.v);
					}
				}
			}
		}
	}
	pair<int, int> solve(int src, int sink) {
		int mc = 0, mf = 0;
		while(1) {
			spfa(src);
			if(par[sink] == -1)
				return {mc, mf};
			int flow = INF, c = sink;
			while(c != src) {
				Edge &e = edges[par[c]];
				flow = min(flow, e.cap-e.flow);
				c = e.u;
			}
			c = sink;
			while(c != src) {
				Edge &e = edges[par[c]], &ie = edges[par[c]^1];
				e.flow += flow;
				ie.flow -= flow;
				c = e.u;
			}
			mf += flow;
			mc += dist[sink]*flow;
		}
	}
};
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n, m, t;
	cin >> n >> m;
	MCMF mcmf(n+m+2);
	for(int i=1; i<=n; i++) {
		cin >> t;
		mcmf.addedge(0, i, 0, t);
	}
	for(int i=n+1; i<=n+m; i++) {
		cin >> t;
		mcmf.addedge(i, n+m+1, 0, t);
	}
	for(int i=n+1; i<=n+m; i++) {
		for(int j=1; j<=n; j++) {
			cin >> t;
			mcmf.addedge(j, i, t, 10086);
		}
	}
	cout << mcmf.solve(0, n+m+1).first;
}
