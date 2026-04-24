#include <bits/stdc++.h>
using namespace std;
const int MX = 1004;
int restr[MX][MX], edge[MX][MX], dist[MX];
vector<pair<int, int>> adj[MX];
vector<int> godula;
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n, m, a, b, k, g;
	cin >> n >> m >> a >> b >> k >> g;
	for(int i=0; i<g; i++) {
		int t;
		cin >> t;
		godula.push_back(t);
	}
	while(m--) {
		int u, v, l;
		cin >> u >> v >> l;
		adj[u].push_back({v,l});
		adj[v].push_back({u,l});
		edge[u][v] = edge[v][u] = l;
	}
	int tm = 0;
	memset(restr, -1, sizeof restr);
	for(int i=1; i<g; i++) {
		int u = godula[i-1], v = godula[i];
		restr[u][v] = restr[v][u] = tm;
		tm += edge[u][v];
	}
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq; // {time, vertex}
	memset(dist, 0x3f, sizeof dist);
	dist[a] = k;
	pq.push({k, a});
	while(1) {
		int u, w;
		tie(w, u) = pq.top();
		pq.pop();
		if(u == b) return !(cout << w-k);
		if(w > dist[u]) continue;
		for(auto pr: adj[u]) {
			int v, pw;
			tie(v, pw) = pr;
			assert(pw == edge[u][v]);
			if(restr[u][v] != -1 && restr[u][v] <= w && w < restr[u][v] + pw) {
				pw = restr[u][v] + pw*2;
			} else {
				pw += w;
			}
			if(pw < dist[v]) {
				dist[v] = pw;
				pq.push({pw, v});
			}
		}
	}
}
