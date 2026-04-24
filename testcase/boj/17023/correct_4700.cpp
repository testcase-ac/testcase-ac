#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MX = 10001;
vector<pair<int, int>> adj[MX];
int cnt[MX], dist[MX], prv[MX], sum[MX];
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n, m, t;
	cin >> n >> m >> t;
	for(int i=1; i<=n; i++) {
		cin >> cnt[i];
	}
	for(int i=0; i<m; i++) {
		int u, v, w;
		cin >> u >> v >> w;
		adj[u].push_back({w, v});
		adj[v].push_back({w, u});
	}
	memset(dist, 0x3f, sizeof dist);
	dist[1] = 0;
	pq.push({0, 1});

	while(pq.size()) {
		auto [w, u] = pq.top();
		pq.pop();
		if(w > dist[u])
			continue;
		for(auto [l, v]: adj[u]) {
			if(w+l < dist[v]) {
				dist[v] = w+l;
				pq.push({dist[v], v});
				prv[v] = u;
			} else if(w+l == dist[v]) {
				prv[v] = min(prv[v], u);
			}
		}
	}
	for(int i=2; i<=n; i++) {
		int x = i;
		while(x != 1) {
			sum[x] += cnt[i];
			x = prv[x];
		}
	}
	for(int i=2; i<=n; i++) {
		sum[i] *= (dist[i] - t);
	}
	cout << max(*max_element(sum+2, sum+n+1), 0ll);
}
