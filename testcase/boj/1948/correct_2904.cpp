#include <bits/stdc++.h>
using namespace std;
struct Edge {
	int u, w;
};
const int MX = 1e4+2;
vector<int> ts;
vector<Edge> adj[MX], adjt[MX];
bool seen[MX];
int dist[MX];
void dfs(int i) {
	seen[i] = 1;
	for(auto e: adj[i]) {
		if(!seen[e.u])
			dfs(e.u);
	}
	ts.push_back(i);
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n, m, ui, ue;
	cin >> n >> m;
	for(int i=0; i<m; i++) {
		int u, v, w;
		cin >> u >> v >> w;
		adj[u].push_back({v,w});
		adjt[v].push_back({u,w});
	}
	cin >> ui >> ue;
	dfs(ui);
	reverse(ts.begin(), ts.end());
	dist[ui] = 0;
	for(int i=0; i<n-1; i++) {
		for(auto e: adj[ts[i]]) {
			dist[e.u] = max(dist[e.u], dist[ts[i]]+e.w);
		}
	}
	cout << dist[ue] << '\n';
	int ans = 0;
	memset(seen, 0, sizeof seen);
	queue<int> que({ue});
	while(!que.empty()) {
		int u = que.front();
		que.pop();
		for(auto e: adjt[u]) {
			if(dist[e.u]+e.w == dist[u]) {
				ans++;
				if(!seen[e.u]) {
					seen[e.u] = 1;
					que.push(e.u);
				}
			}
		}
	}
	cout << ans << '\n';
}
