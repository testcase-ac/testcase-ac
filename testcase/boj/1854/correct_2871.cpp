#include <bits/stdc++.h>
using namespace std;

struct Path {
	int u, w;
	bool operator<(const Path &p) const {
		return w > p.w;
	}
};
const int MX = 1e3+3;
int cnt[MX], dist[MX];
vector<Path> adj[MX];
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	memset(dist, -1, sizeof dist);
	int n, m, k;
	cin >> n >> m >> k;
	priority_queue<Path> pq;
	while(m--) {
		int u, v, w;
		cin >> u >> v >> w;
		u--, v--;
		adj[u].push_back({v,w});
	}
	pq.push({0,0});
	while(!pq.empty()) {
		Path pt = pq.top();
		pq.pop();
		int u = pt.u, w = pt.w;
		if(cnt[u] >= k) continue;
		cnt[u]++;
		if(cnt[u] == k) {
			dist[u] = w;
		}
		for(Path p: adj[u]) {
			if(cnt[p.u] < k)
				pq.push({p.u, w+p.w});
		}
	}
	for(int i=0; i<n; i++) {
		cout << dist[i] << '\n';
	}
}
