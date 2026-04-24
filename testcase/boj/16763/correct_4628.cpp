#include <bits/stdc++.h>
using namespace std;
const int MX = 5e4+2, INF = 0x3f3f3f3f;
struct edge {
	int u, w;
	bool operator<(const edge &e) const {
		return w > e.w;
	}
};
vector<edge> adj[MX];
void dijk(priority_queue<edge> &pq, vector<int>& dist) {
	while(pq.size()) {
		auto [u, w] = pq.top();
		pq.pop();
		if(w > dist[u]) continue;
		for(auto [v, ew]: adj[u]) {
			if(dist[v] > dist[u]+ew) {
				dist[v] = dist[u]+ew;
				pq.push({v, dist[v]});
			}
		}
	}
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n, m, k;
	cin >> n >> m >> k;
	for(int i=0; i<m; i++) {
		int u, v, w;
		cin >> u >> v >> w;
		adj[u].push_back({v, w});
		adj[v].push_back({u, w});
	}
	vector<int> dist(n+1, INF), dist2(n+1, INF);
	dist[n] = 0;
	priority_queue<edge> pq;
	pq.push({n, 0});
	dijk(pq, dist);
	for(int i=0; i<k; i++) {
		int u, w;
		cin >> u >> w;
		dist2[u] = dist[u]-w;
		pq.push({u, dist2[u]});
	}
	dijk(pq, dist2);
	for(int i=1; i<n; i++)
		cout << (dist2[i] <= dist[i]) << '\n';
}
