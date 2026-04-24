#include <bits/stdc++.h>
using namespace std;
const int MX = 20001;
struct Path {
	int v, w;
	bool operator<(const Path &p) const{
		return w > p.w;
	}
};
vector<Path> adj[MX];
int dist[MX];
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n, m, s;
	cin >> n >> m >> s;
	for(int i=0; i<m; i++) {
		int u, v, w;
		cin >> u >> v >> w;
		adj[u].push_back({v, w});
	}
	memset(dist, 0x3f, sizeof dist);
	dist[s] = 0;
	priority_queue<Path> pq;
	pq.push({s, 0});
	while(!pq.empty()) {
		auto t = pq.top();
		int v = t.v, w = t.w;
		pq.pop();
		if(w > dist[v]) continue;
		for(Path p: adj[v]) {
			if(dist[p.v] > dist[v]+p.w) {
				dist[p.v] = dist[v]+p.w;
				pq.push({p.v, dist[p.v]});
			}
		}
	}
	for(int i=1; i<=n; i++) {
		if(dist[i] == 0x3f3f3f3f)
			cout << "INF\n";
		else
			cout << dist[i] << '\n';
	}
}
