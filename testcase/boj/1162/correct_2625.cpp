#include <bits/stdc++.h>
using namespace std;
#define int long long
struct edge {
	int v, w;
	bool operator<(const edge& e) const {
		return w > e.w;
	}
};
int dist[22][10001];
vector<edge> adj[10001];
int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n, m, k;
	cin >> n >> m >> k;
	while(m--) {
		int a, b, w;
		cin >> a >> b >> w;
		adj[a].push_back({b,w});
		adj[b].push_back({a,w});
	}
	memset(dist, 0x3f, sizeof(dist));
	dist[0][1] = 0;
	for(int i=0; i<=k; i++) {
		priority_queue<edge> pq;
		for(int j=1; j<=n; j++) {
			pq.push({j, dist[i][j]});
		}
		while(pq.size()) {
			int v, w;
			auto pr = pq.top();
			pq.pop();
			v = pr.v, w = pr.w;
			if(w > dist[i][v])
				continue;
			for(auto a: adj[v]) {
				if(dist[i][a.v] > w + a.w) {
					dist[i][a.v] = w+a.w;
					pq.push({a.v, w+a.w});
				}
			}
		}
		memcpy(dist[i+1], dist[i], sizeof dist[i]);
		for(int j=1; j<=n; j++) {
			for(auto a: adj[j]) {
				dist[i+1][a.v] = min(dist[i+1][a.v], dist[i][j]);
			}			
		}
	}
	cout << dist[k][n];
}
// 10 50 80 100
