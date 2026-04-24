#include <bits/stdc++.h>
using namespace std;
struct edge {int u, v, w, cap, flow;};
vector<edge> edges;
vector<int> adj[802];
bool inque[802];
int dist[802], prv[802];
void addedge(int u, int v, int w, int cap) {
	adj[u].push_back(edges.size());
	edges.push_back({u, v, w, cap, 0});
	adj[v].push_back(edges.size());
	edges.push_back({v, u, -w, cap, cap});
}
bool spfa(int s, int t) {
	memset(inque, 0, sizeof inque);
	memset(dist, 0x3f, sizeof dist);
	memset(prv, -1, sizeof prv);
	queue<int> que;
	que.push(s);
	dist[s] = 0;
	while(!que.empty()) {
		int q = que.front();
		que.pop();
		inque[q] = 0;
		for(int i: adj[q]) {
			edge &e = edges[i];
			if(e.cap > e.flow && dist[e.v] > dist[e.u]+e.w) {
				dist[e.v] = dist[e.u]+e.w;
				prv[e.v] = i;
				if(!inque[e.v]) {
					inque[e.v] = 1;
					que.push(e.v);
				}
			}

		}
	}
	return prv[t] != -1;
}

void mcmf(int s, int t, int& mc, int& mf) {
	mc = 0, mf = 0;
	while(spfa(s, t)) {
		int flow = INT_MAX, p = t;
		while(p) {
			edge& e = edges[prv[p]];
			flow = min(flow, e.cap-e.flow);
			p = e.u;
		}
		p = t;
		while(p) {
			edge &e = edges[prv[p]], &ie = edges[prv[p]^1];
			e.flow += flow;
			ie.flow -= flow;
			p = e.u;
		}
		mc += dist[t];
		mf += flow;
	}
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n, m;
	cin >> n >> m;
	for(int i=1; i<=n; i++) {
		addedge(0, i, 0, 1);
	}
	for(int i=n+1; i<=n+m; i++) {
		addedge(i, n+m+1, 0, 1);
	}
	for(int i=1; i<=n; i++) {
		int t;
		cin >> t;
		while(t--) {
			int p, w;
			cin >> p >> w;
			addedge(i, n+p, w, 1);
		}
	}
	int mc, mf;
	mcmf(0, n+m+1, mc, mf);
	cout << mf << '\n' << mc;
}
